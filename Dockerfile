FROM gcc

RUN apt-get update && apt-get install -y cmake gdb

WORKDIR /app
