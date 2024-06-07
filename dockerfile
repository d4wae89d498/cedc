# syntax = edrevo/dockerfile-plus
INCLUDE+ debian-llvm.dockerfile

# Copy third-party directory first to leverage caching
COPY third-party /project/third-party
COPY common.mk /project/common.mk

# Set the working directory for the third-party build
WORKDIR /project/third-party

# Install wget, curl, jq, and other dependencies
RUN apt-get update && apt-get install -y wget curl jq openjdk-17-jre-headless

# Grap packages version of locally installed ones
ENV VERSIONS_FILE=versions.txt

# Fetch the latest ANTLR release tag from GitHub and download the jar file
RUN ANTLR_VERSION=4.13.1 && \
    wget http://www.antlr.org/download/antlr-$ANTLR_VERSION-complete.jar -O /usr/local/lib/antlr-$ANTLR_VERSION-complete.jar && \
    echo '#! /bin/bash\n'\
'export CLASSPATH=".:/usr/local/lib/antlr-'$ANTLR_VERSION'-complete.jar:$CLASSPATH"\n'\
'java -jar /usr/local/lib/antlr-'$ANTLR_VERSION'-complete.jar "$@"\n'\
> /usr/local/bin/antlr4 && \
    chmod +x /usr/local/bin/antlr4

# Verify the installation by printing ANTLR version
RUN ln -s /usr/local/bin/antlr4 /usr/bin/antlr4
RUN ln -s $(which antlr4) /usr/bin/antlr

# Build deps and cleanup
RUN make && cd llvm-project && rm -rf llvm \
	&& rm -rf clang \
	&& rm -rf clang-tools-extra \
	&& rm -rf lld \
	&& rm -rf lldb \
	&& rm -rf polly \
	&& rm -rf flang \
	&& rm -rf bolt \
	&& rm -rf mlir \
	&& rm -rf libc

# Copy the main project files
COPY . /project/

# Set the working directory for the main project
WORKDIR /project/

# Build the main project
RUN make

# Run the tests
RUN make test
