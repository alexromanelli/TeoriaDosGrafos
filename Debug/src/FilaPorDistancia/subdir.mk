################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FilaPorDistancia/FilaPorDistancia.cpp \
../src/FilaPorDistancia/FilaPorDistanciaVector.cpp 

OBJS += \
./src/FilaPorDistancia/FilaPorDistancia.o \
./src/FilaPorDistancia/FilaPorDistanciaVector.o 

CPP_DEPS += \
./src/FilaPorDistancia/FilaPorDistancia.d \
./src/FilaPorDistancia/FilaPorDistanciaVector.d 


# Each subdirectory must supply rules for building sources it contributes
src/FilaPorDistancia/%.o: ../src/FilaPorDistancia/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


