#include <engine++.h>
#include <sg_as.h>

using namespace its;
using namespace std;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int main(const int argc, const char **argv)
{
    int i = 0;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp("asp", argv[i]) == 0)
        {
            appMode = ASP_MODE;
        }
        else if (strcmp("sgp", argv[i]) == 0)
        {
            appMode = SGP_MODE;
        }
        else if (strcmp("dpc", argv[i]) == 0)
        {
            i++;
            app_dpc = RESFILE_ParseNum(argv[i]);
        }
        else if (strcmp("dssn", argv[i]) == 0)
        {
            i++;
            app_dssn = RESFILE_ParseNum(argv[i]);
        }
        else if (strcmp("opc", argv[i]) == 0)
        {
            i++;
            app_opc = RESFILE_ParseNum(argv[i]);
        }
        else if (strcmp("ossn", argv[i]) == 0)
        {
            i++;
            app_ossn = RESFILE_ParseNum(argv[i]);
        }
    }

    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    return 0;
}
