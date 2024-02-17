#pragma once

#include <vector>

#include <cstring>

namespace trsap {
	extern "C" {
		#include "trsap.h"
	}

	using Arg = trsap_Arg;
	using ArgDesc = trsap_ArgDesc;
	using ArgValueType = trsap_ArgValueType;

    /*
	 * trsap::chop (aka trsap_chopArg)
	 * @param argc - a ptr to argc
	 * @param argv - a ptr to argv
	 * @return choped argument if exists or 0.
 	 * @description If there is any argument in argv (argc > 0) then argc will be decrised and argv shifted.
 	 */
	inline const char* chop(int* argc, const char*** argv){
        return trsap_chopArg(argc, argv);
    }

	/*
	 * trsap::get (aka trsap_getArg)
	 * @param argc - a ptr to argc
	 * @param argv - a ptr to argv
	 * @param descs - the arguments descriptions 
	 * @return first argument's info or trsap_arg in error mode (m_Error != 0).
	 * @description If there is any arg left then it will be poped (with value depends of description) and returned in trsap_Arg format.
	 */
	inline Arg get(int* argc, const char*** argv, ArgDesc* descs){
		return trsap_getArg(argc, argv, descs);
	}

	/*
	 * trsap::getAll
	 * @param argc - the argc
	 * @param argv - the argv
	 * @param descs - the arguments descriptions 
	 * @return a std::vector of Arg (aka trsap_Arg) of parsed arguments 
	 * @description Uses trsap::get in a loop to parse all cli arguments (or to first error).
	 */
	inline std::vector<Arg> getAll(int argc, const char** argv, ArgDesc* descs){
		std::vector<Arg> r;

		Arg a = get(&argc, &argv, descs);
		while((a.m_ID || a.m_Value) && !a.m_Error){
			r.push_back(a);
			a = get(&argc, &argv, descs);
		}

		if(a.m_Error)
			r.push_back(a);

		return r;
	}
}

