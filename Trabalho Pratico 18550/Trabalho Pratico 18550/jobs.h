#pragma once

#include "operations.h";

typedef struct Job {
	int cod;
	struct OperationsList* operations;
}Job;

typedef struct ProcessPlan {
	struct Job job;
	struct ProcessPlan* nextJob;
}ProcessPlan;