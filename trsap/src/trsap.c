#include <trsap.h>

#include <string.h>
#include <stdbool.h>

const char* trsap_chopArg(int* argc, const char*** argv){
	if(*argc <= 0)
		return 0;

    const char* arg = (*argv)[0];
    (*argv)++;
    (*argc)--;
    return arg;
}

trsap_Arg trsap_getArg(int* argc, const char*** argv, trsap_ArgDesc* descs){
	trsap_Arg r = {0, 0, 0, 0};

	const char* arg = trsap_chopArg(argc, argv);
	if(!arg)
		return r;

	bool ul = false;
	
	if(arg[0] == '-'){
        r.m_Tag = arg;
		arg++;
		if(arg[0] == '-'){
			arg++;
			ul = true;
		}
	} else{
		r.m_Value = arg;
		return r;
	}

	size_t i = 0;
	trsap_ArgValueType type = TRSAP_ARG_VALUE_TYPE_ERROR;

	const char* value = 0;
	size_t arg_len = strlen(arg);
	while(descs[i].m_Type){
		if(ul && descs[i].m_Long){
			size_t len = strlen(descs[i].m_Long);
			if(arg_len >= len && strncmp(descs[i].m_Long, arg, len) == 0){
				if(arg_len > len){
					if(arg[len] == '=') 
						value = &arg[len + 1];
					else
						continue;
				}

				type = descs[i].m_Type;
				break;
			}
		} else if(!ul){
			if(arg[0] == descs[i].m_Short){
				if(arg_len > 1){
					value = &arg[1];
				}

				type = descs[i].m_Type;
				break;
			}
		}
		/*if((ul && descs[i].m_Long && strcmp(arg, descs[i].m_Long) == 0) || (!ul && arg[0] == descs[i].m_Short)){
			type = descs[i].m_Type;
			break;
		}*/
		i++;
	}

	switch(type){
		case TRSAP_ARG_VALUE_TYPE_EXPECT:
			if(value)
				r.m_Value = value;
			else if(*argc > 0)
				r.m_Value = trsap_chopArg(argc, argv);
			else
				r.m_Error = 1;
			break;
		case TRSAP_ARG_VALUE_TYPE_OPTIONAL:
			if(value)
				r.m_Value = value;
			else if(*argc > 0 && (*argv)[0][0] != '-')
				r.m_Value = trsap_chopArg(argc, argv);
			break;
		case TRSAP_ARG_VALUE_TYPE_NONE:
			if(value)
				r.m_Error = 3;
			break;
		case TRSAP_ARG_VALUE_TYPE_ERROR:
			r.m_Error = 2;
			break;
        default:
            r.m_Error = 4;
	}

	r.m_ID = i + 1;
	return r;
}

