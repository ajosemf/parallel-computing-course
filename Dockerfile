FROM ubuntu:20.04
LABEL author="ajosemf@gmail.com"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y \
       cmake \
       wget \
       build-essential \
       manpages-dev \
       git \
       libomp-dev \
    && apt clean

WORKDIR /home
