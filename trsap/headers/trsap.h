#ifndef _TRSAP_H_
#define _TRSAP_H_

#include <stddef.h>

/*
 * enum trsap_ArgValueType
 * @description An enum of arg's expectations.
 */
typedef enum{
	TRSAP_ARG_VALUE_TYPE_ERROR = 0,
	TRSAP_ARG_VALUE_TYPE_NONE = 1,
	TRSAP_ARG_VALUE_TYPE_EXPECT = 2,
	TRSAP_ARG_VALUE_TYPE_OPTIONAL = 3
} trsap_ArgValueType;

/*
 * struct trsap_Arg
 * @description The struct holds data about one parsed argument.
 */
typedef struct{
	size_t m_ID;
	const char* m_Value;
    const char* m_Tag;
	char m_Error;
} trsap_Arg;

/*
 * struct trsap_ArgDesc
 * @description The struct describes an argument.
 */
typedef struct{
	char m_Short;
	const char* m_Long;
	trsap_ArgValueType m_Type;
} trsap_ArgDesc;

/*
 * trsap_chopArg
 * @param argc - a ptr to argc
 * @param argv - a ptr to argv
 * @return choped argument if exists or 0.
 * @description If there is any argument in argv (argc > 0) then argc will be decrised and argv shifted.
 */
const char* trsap_chopArg(int* argc, const char*** argv);

/*
 * trsap_getArg
 * @param argc - a ptr to argc
 * @param argv - a ptr to argv
 * @param descs - the arguments descriptions 
 * @return first argument's info or trsap_arg in error mode (m_Error != 0).
 * @description If there is any arg left then it will be poped (with value depends of description) and returned in trsap_Arg format.
 */
trsap_Arg trsap_getArg(int* argc, const char*** argv, trsap_ArgDesc* descs);

#endif // _TRSAP_H_
