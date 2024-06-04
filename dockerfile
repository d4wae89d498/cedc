# syntax = edrevo/dockerfile-plus
INCLUDE+ debian-llvm.dockerfile

# Copy third-party directory first to leverage caching
COPY third-party /project/third-party

# Set the working directory for the third-party build
WORKDIR /project/third-party

# Build the third-party dependencies
RUN make

# Copy the main project files

# syntax=docker.io/docker/dockerfile:1.7-labs
COPY --exclude=third-party . /project/

# Set the working directory for the main project
WORKDIR /project/

# Build the main project
RUN make

# Run the tests
RUN make test
