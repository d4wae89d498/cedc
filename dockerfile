# syntax = edrevo/dockerfile-plus
INCLUDE+ debian-llvm.dockerfile

# Install wget, curl, jq, and other dependencies
RUN apt-get update && apt-get install -y wget curl jq default-jdk

# Fetch the latest ANTLR release tag from GitHub and download the jar file
RUN LATEST_VERSION=$(curl -s https://api.github.com/repos/antlr/antlr4/releases/latest | jq -r '.tag_name') && \
    wget http://www.antlr.org/download/antlr-$LATEST_VERSION-complete.jar -O /usr/local/lib/antlr-$LATEST_VERSION-complete.jar && \
    echo '#! /bin/bash\n'\
'export CLASSPATH=".:/usr/local/lib/antlr-'$LATEST_VERSION'-complete.jar:$CLASSPATH"\n'\
'java -jar /usr/local/lib/antlr-'$LATEST_VERSION'-complete.jar "$@"\n'\
> /usr/bin/antlr4 && \
    chmod +x /usr/bin/antlr4

# Verify the installation by printing ANTLR version
RUN antlr4 -version
RUN ln -s $(which antlr4) /usr/bin/antlr

# Copy third-party directory first to leverage caching
COPY third-party /project/third-party
COPY common.mk /project/common.mk

# Set the working directory for the third-party build
WORKDIR /project/third-party

# Build the third-party dependencies
RUN make

# Copy the main project files
COPY . /project/

# Set the working directory for the main project
WORKDIR /project/

# Build the main project
RUN make

# Run the tests
RUN make test
