#ifndef _MY_PACKAGE_ETWCONSUMER_HPP_
#define _MY_PACKAGE_ETWCONSUMER_HPP_

#pragma once

#include "TraceConsumer.hpp"
#include "TraceSession.h"

int Begin(void (*c)(char* n));

#endif