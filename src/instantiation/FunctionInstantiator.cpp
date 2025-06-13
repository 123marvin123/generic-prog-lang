
#include "instantiation/FunctionInstantiator.h"

Function* FunctionInstantiator::instantiate(CongParser::FunctionStmntContext* ctx, Namespace* ns,
                                            const bool declarationOnly)
{
    Visitor v{ns, declarationOnly};

    if (const std::any result = v.visit(ctx); result.has_value() && result.type() == typeid(Function*))
        return std::any_cast<Function*>(result);

    throw SemaError("Could not instantiate function", ctx);
}

std::any FunctionInstantiator::Visitor::visitFunctionStmnt(CongParser::FunctionStmntContext* ctx)
{
    const std::string& name = ctx->name->getText();

    if (declarationOnly)
    {
        if (const auto resulting_parameters = visit(ctx->parameterList());
            resulting_parameters.has_value() && resulting_parameters.type() == typeid(vec<FunctionParameter*>))
        {
            const auto& parameters = std::any_cast<vec<FunctionParameter*>>(resulting_parameters);
            bool isDependent = std::ranges::any_of(
                parameters, [](const auto* p)
                { return utils::is<DependentFunctionParameter>(p) || utils::is<PlaceholderFunctionParameter>(p); });

            const std::any& function_result = visit(ctx->type);
            if (!function_result.has_value() || function_result.type() != typeid(utils::FQIInfo))
                throw SemaError(std::format("Could not parse function return concept {}", ctx->type->getText()),
                                ctx->type);

            const utils::FQIInfo& fqi = std::any_cast<utils::FQIInfo>(function_result);
            if (const auto& resulting_concept = resolve_fully_qualified_identifier<Concept>(fqi, ns);
                resulting_concept.has_value() && resulting_concept.value())
            {
                isDependent = false;
                if (const auto& res = Sema::create_function<ConcreteFunction>(ns, name, ns, resulting_concept.value());
                    res.has_value())
                    current_function = res.value();
                else
                    throw SemaError(std::format("Could not instantiate function {} because it already exist", name),
                                    ctx);
            }
            else if (!isDependent)
                throw SemaError(std::format("Could not instantiate function {} because concept {} was not found",
                name, ctx->type->getText()),
                ctx->type);

            if (isDependent)
            {
                PlaceholderFunctionParameter* target_placeholder = nullptr;
                for (auto* p : parameters)
                {
                    if (!utils::is<PlaceholderFunctionParameter>(p))
                        continue;

                    auto* cast = utils::dyn_cast<PlaceholderFunctionParameter>(p);
                    if (cast->get_type_placeholder_name() != fqi.identifier)
                        continue;

                    target_placeholder = cast;
                    break;
                }

                if (!target_placeholder)
                    throw SemaError(std::format("Could not find placeholder {}", fqi.identifier), ctx->type);

                if (const auto& res = Sema::create_function<DependentFunction>(ns, name, ns); res.has_value())
                {
                    current_function = res.value();
                    res.value()->set_dependency(target_placeholder);
                }
                else
                    throw SemaError(std::format("Could not instantiate function {} because it already exists", name), ctx);
            }

            for (FunctionParameter* fp : parameters)
                current_function->register_function_parameter(std::unique_ptr<FunctionParameter>(fp));
        }
        else
            throw SemaError("Could not parse function parameters", ctx->parameterList());

        return current_function;
    }

    const opt<Function*> fn = ns->find_function(name);
    if (!fn.has_value() || !fn.value())
        throw SemaError(std::format("Could not find function {}", name), ctx);

    current_function = fn.value();

    visit(ctx->functionBody());

    return current_function;
}

std::any FunctionInstantiator::Visitor::visitParameterList(CongParser::ParameterListContext* ctx)
{
    vec<FunctionParameter*> parameters;
    placeholders.clear();
    for (CongParser::ParameterContext* c : ctx->parameter())
    {
        if (const std::any result = visit(c); result.has_value() && result.type() == typeid(FunctionParameter*))
        {
            parameters.push_back(std::any_cast<FunctionParameter*>(result));
        }
        else
            throw SemaError(std::format("Could not parse parameter {}", c->getText()), c);
    }

    return parameters;
}

std::any FunctionInstantiator::Visitor::visitParameter(CongParser::ParameterContext* ctx)
{
    const std::string name = ctx->name->getText();
    const std::any result = visit(ctx->type);
    if (!result.has_value())
        throw SemaError(std::format("Could not parse parameter {}", ctx->type->getText()), ctx->type);

    if (result.type() == typeid(utils::FQIInfo))
    {
        const auto& fqi = std::any_cast<utils::FQIInfo>(result);
        auto c = resolve_fully_qualified_identifier<Concept>(fqi, ns);
        if (c.has_value())
            return utils::dyn_cast<FunctionParameter>(new ConcreteFunctionParameter(name, c.value()));

        if (const auto& it = std::ranges::find_if(placeholders, [&fqi](const auto& p)
                                                  { return p->get_type_placeholder_name() == fqi.identifier; });
            it != placeholders.end())
            return utils::dyn_cast<FunctionParameter>(new DependentFunctionParameter(name, *it));

        throw SemaError(std::format("Could not find concept or placeholder {}", ctx->type->getText()), ctx->type);
    }

    if (result.type() == typeid(Placeholder))
    {
        const auto p = std::any_cast<Placeholder>(result);
        placeholders.push_back(new PlaceholderFunctionParameter(name, p.name));
        return utils::dyn_cast<FunctionParameter>(placeholders.back());
    }

    throw SemaError(std::format("Could not parse parameter {}", ctx->type->getText()), ctx->type);
}

std::any FunctionInstantiator::Visitor::visitQualifiedIdentifier(CongParser::QualifiedIdentifierContext* ctx)
{
    return utils::split_fully_qualified_identifier(ctx->getText());
}

std::any FunctionInstantiator::Visitor::visitPlaceholder(CongParser::PlaceholderContext* ctx)
{
    return Placeholder{ctx->name->getText()};
}
