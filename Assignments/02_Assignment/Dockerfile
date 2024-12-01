# Setup the baseimage
FROM gcc:latest

# Set working directory
WORKDIR /app 

# Copy the source code to the container
COPY main.cpp .

# Compile C++ program
RUN g++ -o main main.cpp

# Execute .exe file
CMD [ "./main" ]