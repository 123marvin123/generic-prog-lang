FROM gcc:14
LABEL authors="Marvin Haschker"

RUN apt-get update &&  \
    apt-get install -y cmake make

# Cleanup unneeded files for docker image
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/* \
