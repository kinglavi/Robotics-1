################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Obstacle.cpp \
../Particle.cpp \
../Position.cpp \
../Robot.cpp \
../main.cpp 

OBJS += \
./Obstacle.o \
./Particle.o \
./Position.o \
./Robot.o \
./main.o 

CPP_DEPS += \
./Obstacle.d \
./Particle.d \
./Position.d \
./Robot.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


