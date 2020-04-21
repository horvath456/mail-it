#pragma once

#include <string>
#include <vector>
#include <functional>
#include <utility>

#include "job.h"
#include "receipent.h"

namespace JobSender
{
void send_job(Job job, std::string jobfile, std::vector<Receipent> all_receipents, std::function<void(std::string, std::string, std::string)>);
}