{% set project_upper=upper(project) %}

#ifndef {{project_upper}}_CONCEPT_H
#define {{project_upper}}_CONCEPT_H

{% set concepts = get_concepts() -%}
{% for i in concepts -%}
	{% set resolve_result = resolve_concept(i.full_name) -%}
    {% if resolve_result.resolved -%}
    	{% set c = resolve_result.result -%}
{% if length(c.namespace) > 0 %} namespace {{ join(c.namespace, "::") }} { {% endif %}

struct {{ postfix(c.name, "Concept") }}
{
    using Bases = std::tuple<{{join(postfix(c.bases, "Concept"), ", ")}}>;
    static constexpr auto description = "{{c.description}}";
};

{% if length(c.namespace) > 0 %} } {% endif %}
    {% endif -%}
{% endfor -%}

#endif //{{project_upper}}_CONCEPT_H

{{get_functions()}}
