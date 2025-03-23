FROM gcc:latest
LABEL authors="Marvin Haschker"

RUN apt update &&  \
    apt install -y cmake make

# Cleanup unneeded files for docker image
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*