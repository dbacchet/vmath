FROM ubuntu:24.04
LABEL maintainer="Davide"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
        build-essential \
        gdb \
        lcov \
        git \
        vim \
        wget \
        htop \
        unzip \
        # openjdk is needed for bazel coverage
        default-jdk \
    && rm -rf /var/lib/apt/lists/*

# Install bazelisk as `bazel`: it reads the version pinned in .bazelversion
# and fetches the matching bazel release automatically.
RUN wget -O /usr/local/bin/bazel \
        https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 \
    && chmod +x /usr/local/bin/bazel
