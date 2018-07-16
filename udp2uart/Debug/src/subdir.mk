################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PackageQueue.cpp \
../src/PracticalSocket.cpp \
../src/SerialLib.cpp \
../src/TcpSocket.cpp \
../src/udp2uart.cpp 

OBJS += \
./src/PackageQueue.o \
./src/PracticalSocket.o \
./src/SerialLib.o \
./src/TcpSocket.o \
./src/udp2uart.o 

CPP_DEPS += \
./src/PackageQueue.d \
./src/PracticalSocket.d \
./src/SerialLib.d \
./src/TcpSocket.d \
./src/udp2uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabi-g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


