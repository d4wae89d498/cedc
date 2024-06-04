# syntax = edrevo/dockerfile-plus
INCLUDE+ debian-llvm.dockerfile

# Set the working directory for the third-party build
WORKDIR /third-party

# Copy third-party directory first to leverage caching
COPY third-party /third-party

# Initialize and update git submodules
RUN git submodule init && git submodule update

# Build the third-party dependencies
RUN make

# Set the working directory for the main project
WORKDIR /app

# Copy the main project files
COPY . /app

# Build the main project
RUN make

# Run the tests
RUN make test
