FROM gcc:14
LABEL authors="Marvin Haschker"

# hadolint ignore=DL3008
RUN apt-get update &&  \
    apt-get install --no-install-recommends -y cmake make

# Cleanup unneeded files for docker image
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/* \
