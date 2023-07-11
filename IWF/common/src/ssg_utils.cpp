/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: ssg_utils.cpp,v 1.1.1.1.2.1 2013/05/20 08:56:40 jvikram Exp $
 *
 *  LOG: $Log: ssg_utils.cpp,v $
 *  LOG: Revision 1.1.1.1.2.1  2013/05/20 08:56:40  jvikram
 *  LOG: Corrected Coverity Issues
 *  LOG:
 *  LOG: Revision 1.2  2013/05/20 04:43:09  jenkins
 *  LOG: Fix for coverity warnings
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:38  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ssg_utils.cpp,v 1.1.1.1.2.1 2013/05/20 08:56:40 jvikram Exp $"

#include <ssg_utils.h>

void PrintEvent(ITS_EVENT* evt)
{
    if (SSG_TRACE()->IsDebugEnabled())
    {
        int x = 0;
        printf("Event source 0x%02x\n",evt->src);
        printf("Event Len %d\n",evt->len);
        for(x = 0; x < evt->len; x++)
        {
            if(x != 0 && x % 8 == 0)
            {
                printf("\n");
            }
            printf("0x%02x, ",evt->data[x]);
        }
        printf("\n");
        fflush(stdout);
    }

    return;
}

void PrintHex(const unsigned char*data, ITS_INT len)
{
    if (SSG_TRACE()->IsDebugEnabled())
    {
        int x = 0;
        printf("Data Len %d\n",len);
        for(x = 0; x<len; x++)
        {
            if(x != 0 && x % 8 == 0)
            {
                printf("\n");
            }
            printf("0x%02x, ",data[x]);
        }
        printf("\n");
        fflush(stdout);
    }

    return;
}

void 
SsgUtils::ConvertBCDToAscii(char* asciidata, char* bcddata,
                       ITS_INT bcdlen)
{
    ITS_INT i;
    ITS_INT j = 0;
    ITS_OCTET temp = 0;
    ITS_OCTET nullset = ITS_FALSE;

    for (i = 0; i < bcdlen; i++)
    {
        asciidata[j++] = (bcddata[i] & 0x0F) + '0';
        temp = (bcddata[i] & 0xF0) >> 4;
        if (temp == 0x0F)
        {
            asciidata[j++] = '\0';
            nullset = ITS_TRUE;
            break;
        }
        else
        {
            asciidata[j++] = temp + '0';
        }
    }
    if (!nullset)
    {
        asciidata[j] = '\0';
    }
}

void 
SsgUtils::ConvertAsciiToBCD(ITS_OCTET* bcgarr, ITS_OCTET *asciidata, ITS_INT asciilen)
{
    ITS_INT i, j = 0;

    for(i = 0; i < asciilen/2; i++)
    {
        bcgarr[i] = asciidata[j++] & 0x0F;
        bcgarr[i] |= (asciidata[j++] & 0x0F) << 4;
    }

    if ((asciilen % 2) != 0)
    {
        bcgarr[i] = asciidata[j] & 0x0F;
        bcgarr[i] |= 0xF0;
    }
}

void
SsgUtils::ConvertStringToOctets(ITS_OCTET* octs, std::string& str,
                                      int& gtt_len, ITS_BOOLEAN& eFlag)
{
   int arr_len = 0;

   if(str.length() % 2 == 0)
   {
      eFlag = ITS_TRUE;
   }

   str = (str.length() %2 == 1) ? str + '0' : str;

   arr_len = str.length() / 2;
   int j = 0;

   for(int i = 0; j < arr_len; i += 2, j++)
   {
      octs[j] = str.at(i + 1) - '0';
      octs[j] <<= 4;
      octs[j] |= str.at(i) - '0';
   }
   if(!eFlag)
   {
       octs[j-1] |= 0x00;
   }

   gtt_len = j;

   if (SSG_TRACE()->IsDebugEnabled())
   {
       for(int i = 0; i < gtt_len; i++)
       {
           printf("%02x ", octs[i]);
       }
   }
   return;
}

void
SsgUtils::ConvertStringToOctets(ITS_OCTET* octs, char* str,
                                      int& gtt_len, ITS_BOOLEAN& eFlag)
{

   bool isOdd;
   int len = 0;
   int i,j;

   len = strlen(str);
   isOdd = (len % 2 == 0) ? false : true;
   i = 0;
   for (j = 0; j < len; i++, j += 2)
   {
       if ((j + 1) < len )
       {
           octs[i] |= (str[j+1] & 0x0FU) << 4;
       }
       octs[i] |= (str[j] & 0x0FU);
   }
   if (isOdd)
   {
       octs[i-1] |= 0x00;
   }
   gtt_len = i;

   if (SSG_TRACE()->IsDebugEnabled())
   {
       printf("ConvertStringToOctets:: GTT String\n");
       for (int i=0; i < gtt_len; i++)
       {
           printf("%02x ", octs[i]);
       }
       printf("\n");
   }
}

void
SsgUtils::ConvertOctsToString(char** str, ITS_OCTET* octs,
                                    int len, ITS_BOOLEAN eFlag)
{
   *str = (char*)calloc(len * 2, sizeof(char));

   if(*str == NULL)
   {
      return;
   }

   for(int i = 0, j = 0; i < len; i++)
   {
       (*str)[j++] = (octs[i] & 0x0F) + '0';

       if(!eFlag && i == len-1)
       {
          /* odd number of digits present */
          break;
       }

       (*str)[j++] = ((octs[i] & 0xF0) >> 4) + '0';
   }

   return;
}


/*
 ****************************************************************************
 *  Purpose:  () is used to convert mdn data into 
 *	         SSG  - ISDN Address String
 * 	         ANSI - MDN  
 *  
 *  Input Parameters:
 *     digits.
 *  
 *  Output Parameters:
 *     ByteArry 
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void
SsgUtils::ConvertToByteArray(ByteArray &array, char *digits, 
                                                  ITS_OCTET npnValue) 
{
    ITS_OCTET buf[ITS_PATH_MAX];
    bool isOdd;
    ITS_INT i,j;
    ITS_INT len = strlen(digits);

    memset(buf, 0, sizeof(buf) / sizeof(ITS_OCTET));

    isOdd = (len % 2 == 0) ? false : true;

    i = 0;
    

    if (npnValue)
    {
       /* ADD NPN */
       //buf[i] = ISDN_EXT | ISDN_TYPE_OF_NUMBER |ISDN_NAI;
       buf[i] = npnValue;
       i++;
    }

    for (j = 0; j < len; i++, j += 2)
    {
        if ((j + 1) < len )
        {
            buf[i] |= (digits[j+1] & 0x0FU) << 4;
        }
        buf[i] |= (digits[j] & 0x0FU);
    }

    if (isOdd)
    {
        buf[i-1] |= 0xF0;
    }

    array.assign(buf, buf + i);
}

int
SsgUtils::CompareStrings(const string& s1, const string& s2)
{
    const string::size_type size1 = s1.size();
    const string::size_type size2 = s2.size();

    // Most frequent case.
    if (size1 != 0 && size1 == size2)
    {
        string::const_reverse_iterator rit1 = s1.rbegin();
        string::const_reverse_iterator rit2 = s2.rbegin();

        int ret = 0;

        while (ret == 0 && rit1 != s1.rend())
        {
            ret = (unsigned char)(*rit1) - (unsigned char)(*rit2);

            rit1++;
            rit2++;
        }

        if (ret < 0)
        {
            return -1;
        }
        else if (ret > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (size1 == 0 && size2 != 0)
    {
        return -1;
    }
    else if (size1 != 0 && size2 == 0)
    {
        return 1;
    }
    else if (size1 == 0 && size2 == 0)
    {
        return 0;
    }
    else    // Different sizes (should be infrequent).
    {
        string::const_reverse_iterator rit1 = s1.rbegin();
        string::const_reverse_iterator rit2 = s2.rbegin();

        int ret = 0;

        while(ret == 0)
        {
            ret = (unsigned char)(*rit1) - (unsigned char)(*rit2);

            if (++rit1 == s1.rend())
            {
                return -1;
            }

            if (++rit2 == s2.rend())
            {
                return 1;
            }
        }
        if (ret < 0)
        {
            return -1;
        }
        else 
        {
            return 1;
        }
    }
}

/*
 ****************************************************************************
 *  Purpose:  Decodies ISdn String 
 *
 *  Input Parameters:
 *      recived Data.
 *  
 *  Input/Output Parameters:
 *      digits.
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
void
SsgUtils::DecodeIsdnString(std::vector<ITS_OCTET> isdnData,
                                     char *digits)
{

    std::vector<ITS_OCTET>::iterator itr;
    int i =0; 
    std::string tempStr; 
    /************************************************************************
    * ISDN-String 
    *     1st Octet - Reserved( 1 MSB bit)|Type Of Number(3 bits) | 
    *		      Numbering Plan Identification( 4 bits)
    *     2nd -N Octets - digits
    ********************************************************************/
    for(itr = isdnData.begin(); itr != isdnData.end();itr++)
    {
       if( i >= 1)
       {
         ITS_OCTET Fdigit = (*(itr)) & 0x0F;
         int tempNum = Fdigit;
         char temp[3]="";
         ITS_OCTET Sdigit = ((*(itr)) & 0xF0) >> 4;
         if(( Sdigit & 0x0F)  != 0x0F)
         {
              tempNum = (tempNum << 4) | Sdigit  ;
              snprintf(temp, sizeof(temp), "%02x", tempNum);
              tempStr.append(temp);

         }
         else
         {
              snprintf(temp, sizeof(temp), "%x", tempNum);
              tempStr.append(temp);
              break;
         }

       }
       i++;
    }
    strncpy(digits, tempStr.c_str(), tempStr.length()); 
    
}

void
SsgUtils::ConvertToFixedByteArray(ByteArray &array, char *digits,int len, 
			                                 ITS_OCTET npnValue)
{
    ITS_OCTET buf[ITS_PATH_MAX];
    bool isOdd;
    ITS_INT i,j;

    memset(buf, 0, sizeof(buf) / sizeof(ITS_OCTET));

    isOdd = (len % 2 == 0) ? false : true;

    i = 0;

    if (npnValue)
    {
        /* ADD NPN */
        //buf[i] = ISDN_EXT | ISDN_TYPE_OF_NUMBER |ISDN_NAI;
        buf[i] = npnValue;

        i++;
    }


    for (j = 0; j < len; i++, j += 2)
    {
        if ((j + 1) < len )
        {
            buf[i] |= (digits[j+1] & 0x0FU) << 4;
        }
        buf[i] |= (digits[j] & 0x0FU);
    }

    if (isOdd)
    {
        buf[i-1] |= 0xF0;
    }

    array.assign(buf, buf + i);
}


/*
 ****************************************************************************
 *  Purpose:  Decodes  String 
 *
 *  Input Parameters:
 *      recived Data.
 *  
 *  Input/Output Parameters:
 *      digits.
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
void
SsgUtils::DecodeBCDString(std::vector<ITS_OCTET> data,
                                     char *digits)
{
    std::vector<ITS_OCTET>::iterator itr;
    int i =0;
    std::string tempStr;

    for(itr=data.begin(); itr!=data.end(); itr++)
    {
       ITS_OCTET Fdigit = (*(itr)) & 0x0F;
       int tempNum = Fdigit;
       char temp[3]="";
       ITS_OCTET Sdigit = ((*(itr)) & 0xF0) >> 4;
       if(( Sdigit & 0x0F ) == 0x0F)
       {
           snprintf(temp, sizeof(temp), "%x", tempNum);
           tempStr.append(temp);
           break;
       }
       else
       {
           tempNum = (tempNum << 4) |Sdigit  ;
           snprintf(temp, sizeof(temp), "%02x", tempNum);
           tempStr.append(temp);
       }
       i++;
    }
    strncpy(digits, tempStr.c_str(), tempStr.length());

}

/*
 ****************************************************************************
 *  Purpose:   ANSI -MSCID Encoding 
 *
 *  Input Parameters:
 *      recived Data.
 *  
 *  Output Parameters:
 *      Byte Array.
 *  
 *  Return Value:
 *      Byte Array.
 *  
 *  Notes:
 * 	 
 *       1-2 Octets -  Market ID - represents Service Provider	 
 *       3rd Octet  -  Switch ID - represents Group of Cell Sites	 
 *
 *  See Also:
 ****************************************************************************/
void
SsgUtils::ConvertToMSCIDByteArray(ByteArray &array, char *digits)
{
    ITS_OCTET buf[ITS_PATH_MAX];
    bool isOdd;
    ITS_INT i,j;
    int len =strlen(digits); 

    memset(buf, 0, sizeof(buf) / sizeof(ITS_OCTET));

    isOdd = (len % 2 == 0) ? false : true;

    i = 0;

    for (j = 0; j < len ; i++)
    {
        buf[i] |= (digits[j] & 0x0FU) << 4;
        buf[i] |= (digits[j+1] & 0x0FU);
        j = j+2;
    }

    array.assign(buf, buf + i);
}
void
SsgUtils::EncodeSsgMsg(AsnObject* p, Octets** octets)
{

    ST_DBG(("SsgUtils::EncodeSsgMsg"));

    if (p == NULL)
    {
        return;
    }

    cout << endl << *p << endl;

    Octets* tmpOctets =NULL;

    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        ST_DBG(("Exception during encoding phase...%s",
                                               exc.GetDescription().c_str()));
        *octets  = NULL;
        return;
    }
    ST_DBG(("--------------------------------------------------"));
    ST_DBG(( "Printing ASN.1 encoded value..."));
    cout << *tmpOctets << endl;

    *octets = tmpOctets;
}

