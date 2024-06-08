FROM whitehat101/cedc-system

# Copy the main project files
COPY . /project/

# Set the working directory for the main project
WORKDIR /project/

# Compiles the app
RUN make
