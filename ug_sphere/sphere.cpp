#include <stdio.h>
#include <uf.h>
#include <uf_modl.h>

#define UF_CALL(X) (report( __FILE__, __LINE__, #X, (X)))

static int report(char *file, int line, char *call, int irc)
{
	if (irc)
	{
		char    messg[133];
		printf("%s, line %d:  %s\n", file, line, call);
		(UF_get_fail_message(irc, messg)) ?
			printf("    returned a %d\n", irc) :
			printf("    returned error %d:  %s\n", irc, messg);
	}
	return(irc);
}

static void do_ugopen_api(void)
{
	//建立球体
	UF_FEATURE_SIGN sign1 = UF_NULLSIGN;// 是否有布尔运算
	tag_t bodySphere = NULL_TAG;
	double center[3] = { 0,0,0 };
	char* D1 = "100";
	tag_t  sphere_tag = NULL_TAG;
	UF_CALL(UF_MODL_create_sphere(sign1, bodySphere, center, D1, &sphere_tag));

	//球体打孔
	UF_FEATURE_SIGN sign2 = UF_NEGATIVE;
	double origin[3] = { 0, 0, -50 };
	char * height = "100";
	char * diam = "30";
	double direction[3] = { 0,0,1 };
	tag_t cyl_obj_id = NULL_TAG;
	UF_CALL(UF_MODL_create_cyl1(sign2, origin, height, diam, direction, &cyl_obj_id));
	double origin1[3] = { 0, -50, 0 };
	double direction1[3] = { 0,1,0 };
	UF_CALL(UF_MODL_create_cyl1(sign2, origin1, height, diam, direction1, &cyl_obj_id));
	double origin2[3] = { -50, 0, 0 };
	double direction2[3] = { 1,0,0 };
	UF_CALL(UF_MODL_create_cyl1(sign2, origin2, height, diam, direction2, &cyl_obj_id));
}

/*ARGSUSED*/
void ufusr(char *param, int *retcode, int paramLen)
{


	if (!UF_CALL(UF_initialize()))
	{
		do_ugopen_api();
		UF_CALL(UF_terminate());
	}
}

int ufusr_ask_unload(void)
{
	return (UF_UNLOAD_IMMEDIATELY);
}
