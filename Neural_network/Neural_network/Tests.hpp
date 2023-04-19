﻿#pragma once

#include <string>
#include<iostream>
#include <vector>
#include<sstream>

#include "Image_conversion.hpp"
#include "Neural_network.hpp"

namespace Testing
{
	void RunAllTests();
	void TestNeuralNetCtor();
	void TestNeuralNetUpdate();
	void TestGetWeights();
	void TestInsertingWeights();
	void TestWritingWeightsToFileANIinsertWeightsToNet();
}
