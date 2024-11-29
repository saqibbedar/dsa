# Base image
FROM gcc:latest

# Set working directory
WORKDIR /app .

# Copy source code
COPY forward_list.cpp .

# Compile c++ program
RUN g++ -o forward_list forward_list.cpp

# Run program
CMD [ "./forward_list" ]