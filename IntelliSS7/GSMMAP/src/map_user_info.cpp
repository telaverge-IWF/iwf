/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2004, IntelliNet Technologies, Inc.                *
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
 *  ID: $Id: map_user_info.cpp,v 1.2 2008/05/01 14:28:16 kramesh Exp $
 ****************************************************************************
 *
 *  LOG: $Log: map_user_info.cpp,v $
 *  LOG: Revision 1.2  2008/05/01 14:28:16  kramesh
 *  LOG: Added new map_user_info file after merging changes from Starhome & Sigvalue
 *  LOG: Branches for the issues 1311 & 1403.
 *  LOG:
 *  LOG: Revision 1.1.2.12  2008/04/15 14:41:42  vkumara
 *  LOG: Fix for ticket #1920
 *  LOG:
 *  LOG: Revision 1.1.2.11  2006/09/19 19:22:26  omayor
 *  LOG: Fix for Validity Period Format (1:enhanced, 2:relative, 3:absolute).
 *  LOG:
 *  LOG: Revision 1.1.2.10  2004/12/27 07:25:21  labuser
 *  LOG: Changes in Print Function.
 *  LOG:
 *  LOG: Revision 1.1.2.9  2004/12/20 12:54:21  mmanikandan
 *  LOG: Coding changes as per SigVal requirement.
 *  LOG:
 *  LOG: Revision 1.1.2.8  2004/11/30 09:47:06  mmanikandan
 *  LOG: Modification 7 bit Alphabet Encoding / Decoding
 *  LOG:
 *  LOG: Revision 1.1.2.7  2004/11/29 11:42:19  mmanikandan
 *  LOG: TBCD Encoding / Decoding modified.
 *  LOG:
 *  LOG: Revision 1.1.2.6  2004/09/08 04:10:45  mmanikandan
 *  LOG: Support for User data header.
 *  LOG:
 *  LOG: Revision 1.1.2.5  2004/08/25 13:54:27  mmanikandan
 *  LOG: Optional in Status report and 7 bit encoding issue is resolved.
 *  LOG:
 *  LOG: Revision 1.1.2.4  2004/07/15 11:13:44  mmanikandan
 *  LOG: Print Compiler error is changed.
 *  LOG:
 *  LOG: Revision 1.1.2.3  2004/07/14 12:51:29  mmanikandan
 *  LOG: Encoding / Decoding for SMS Status Report is added.
 *  LOG:
 *  LOG: Revision 1.1.2.2  2004/06/11 11:51:28  mmanikandan
 *  LOG: Encoding / Decoding of SMSSubmit and SMSDeliver.
 *  LOG:
 *  LOG: Revision 1.1.2.1  2004/06/04 10:25:48  mmanikandan
 *  LOG: Initial commit for map user info encoding / decoding.
 *  LOG:
 *
 ***************************************************************************/

#include <map_user_info.h>
#include <stdio.h>
#include <string>
#define NPC7    63
#define NPC8    '?'

using namespace std;

int CalculateValidityPeriod (ITS_OCTET vpFormat,
                             ITS_OCTET* vpOctet,
                             ValidityPeriod* vp)
{
    ITS_INT ret = ITS_SUCCESS;

    memset (vp, 0, sizeof(ValidityPeriod));

    if (!vpOctet || !vp) 
    {
        return -2;
    }

    if ((vpFormat == 3) && ((vpOctet[0] & 0x07) == 0x01))
    {
        vpFormat = MAP_VP_FORMAT_RELEATIVE;
        vpOctet++;
    }
    
    switch (vpFormat)
    {
        case MAP_VP_FORMAT_ABSOLUTE:
        {
            vp->day = (vpOctet[2] & 0x0f) << 4 |
                      (vpOctet[2] & 0xf0) >> 4;
            vp->month = (vpOctet[1] & 0x0f) << 4 |
                        (vpOctet[1] & 0xf0) >> 4;
            vp->year = (vpOctet[0] & 0x0f) << 4 |
                       (vpOctet[0] & 0xf0) >> 4;
            vp->hour = (vpOctet[3] & 0x0f) << 4 |
                       (vpOctet[3] & 0xf0) >> 4;
            vp->minute = (vpOctet[4] & 0x0f) << 4 |
                         (vpOctet[4] & 0xf0) >> 4;
            vp->second = (vpOctet[5] & 0x0f) << 4 |
                         (vpOctet[5] & 0xf0) >> 4;
            vp->timezone = (vpOctet[6] & 0x0f) << 4 |
                           (vpOctet[6] & 0xf0) >> 4;
            break;
        }
        case MAP_VP_FORMAT_RELEATIVE:
        {
            int val = vpOctet[0];

            if ((val >= 0) && (val <= 143))
            {
                vp->tpvpValue = (val + 1) * 5 * 60;
            }
            else if ((val >= 144) && (val <= 167))
            {
                vp->tpvpValue = ((val - 143) * 30 * 60) +
                                (12 * 60 * 60);
            }
            else if ((val >= 168) && (val <= 196))
            {
                vp->tpvpValue = (val - 166) * 24 * 60 * 60;
            }
            else if ((val >= 197) && (val <= 255))
            {
                vp->tpvpValue = (val - 192) * 7 * 24 * 60 * 60;
            }

            break;
        }
        case MAP_VP_FORMAT_ENHANCED:
        {
            if ((vpOctet[0] & 0x07) == 0x02)
            {
                vp->tpvpValue = vpOctet[1];
            }
            else if ((vpOctet[0] & 0x07) == 0x03)
            { 
                vp->hour = ((vpOctet[1] & 0x0f) << 4) |
                           ((vpOctet[1] & 0xf0) >> 4);
                vp->minute = ((vpOctet[2] & 0x0f) << 4) |
                             ((vpOctet[2] & 0xf0) >> 4);
                vp->second = ((vpOctet[3] & 0x0f) << 4) |
                             ((vpOctet[3] & 0xf0) >> 4);
            }
            break;
        }
        default:
        {
            ret = -1;
            break;
        }
    }

    return ret;
}

static char GetTBCDCharacter(char valch)
{
    char ch = 0;
    if ((valch >= 0) && (valch <= 9))
    {
        ch = valch + '0';        
    }
    else 
    {
        switch (valch)
        {
        case 10:
            ch = '*';
            break;
        case 11:
            ch = '#';
            break;
        case 12:
            ch = 'a';
            break;
        case 13:
            ch = 'b';
            break;
        case 14:
            ch = 'c';
        }
    }
    return ch;
}

static char SetTBCDCharacter(char valch)
{
    char ch = 0;
    if ((valch >= '0') && (valch <= '9'))
    {
        ch = valch - '0';        
    }
    else 
    {
        switch (valch)
        {
        case '*':
            ch = 10;
            break;
        case '#':
            ch = 11;
            break;
        case 'a':
            ch = 12;
            break;
        case 'b':
            ch = 13;
            break;
        case 'c':
            ch = 14;
        }
    }
    return ch;
}

/* Define Non-Printable Characters as a question mark */

/****************************************************************************
    This lookup table converts from ISO-8859-1 8-bit ASCII to the
    7 bit "default alphabet" as defined in ETSI GSM 03.38

    ISO-characters that don't have any correspondning character in the
    7-bit alphabet is replaced with the NPC7-character.  If there's
    a close match between the ISO-char and a 7-bit character (for example
    the letter i with a circumflex and the plain i-character) a substitution
    is done. These "close-matches" are marked in the lookup table by
    having its value negated.
    
    There are some character (for example the curly brace "}") that must
    be converted into a 2 byte 7-bit sequence.  These characters are
    marked in the table by having 256 added to its value.              
****************************************************************************/

int lookup_ascii8to7[]={
    NPC7,       /*     0      null [NUL]                              */
    NPC7,       /*     1      start of heading [SOH]                  */
    NPC7,       /*     2      start of text [STX]                     */
    NPC7,       /*     3      end of text [ETX]                       */
    NPC7,       /*     4      end of transmission [EOT]               */
    NPC7,       /*     5      enquiry [ENQ]                           */
    NPC7,       /*     6      acknowledge [ACK]                       */
    NPC7,       /*     7      bell [BEL]                              */
    NPC7,       /*     8      backspace [BS]                          */
    NPC7,       /*     9      horizontal tab [HT]                     */
    10,         /*    10      line feed [LF]                          */
    NPC7,       /*    11      vertical tab [VT]                       */
    10+256,     /*    12      form feed [FF]                          */
    13,         /*    13      carriage return [CR]                    */
    NPC7,       /*    14      shift out [SO]                          */
    NPC7,       /*    15      shift in [SI]                           */
    NPC7,       /*    16      data link escape [DLE]                  */
    NPC7,       /*    17      device control 1 [DC1]                  */
    NPC7,       /*    18      device control 2 [DC2]                  */
    NPC7,       /*    19      device control 3 [DC3]                  */
    NPC7,       /*    20      device control 4 [DC4]                  */
    NPC7,       /*    21      negative acknowledge [NAK]              */
    NPC7,       /*    22      synchronous idle [SYN]                  */
    NPC7,       /*    23      end of trans. block [ETB]               */
    NPC7,       /*    24      cancel [CAN]                            */
    NPC7,       /*    25      end of medium [EM]                      */
    NPC7,       /*    26      substitute [SUB]                        */
    NPC7,       /*    27      escape [ESC]                            */
    NPC7,       /*    28      file separator [FS]                     */
    NPC7,       /*    29      group separator [GS]                    */
    NPC7,       /*    30      record separator [RS]                   */
    NPC7,       /*    31      unit separator [US]                     */
    32,         /*    32      space                                   */
    33,         /*    33    ! exclamation mark                        */
    34,         /*    34    " double quotation mark                   */
    35,         /*    35    # number sign                             */
    2,          /*    36    $ dollar sign                             */
    37,         /*    37    % percent sign                            */
    38,         /*    38    & ampersand                               */
    39,         /*    39    ' apostrophe                              */
    40,         /*    40    ( left parenthesis                        */
    41,         /*    41    ) right parenthesis                       */
    42,         /*    42    * asterisk                                */
    43,         /*    43    + plus sign                               */
    44,         /*    44    , comma                                   */
    45,         /*    45    - hyphen                                  */
    46,         /*    46    . period                                  */
    47,         /*    47    / slash,                                  */
    48,         /*    48    0 digit 0                                 */
    49,         /*    49    1 digit 1                                 */
    50,         /*    50    2 digit 2                                 */
    51,         /*    51    3 digit 3                                 */
    52,         /*    52    4 digit 4                                 */
    53,         /*    53    5 digit 5                                 */
    54,         /*    54    6 digit 6                                 */
    55,         /*    55    7 digit 7                                 */
    56,         /*    56    8 digit 8                                 */
    57,         /*    57    9 digit 9                                 */
    58,         /*    58    : colon                                   */
    59,         /*    59    ; semicolon                               */
    60,         /*    60    < less-than sign                          */
    61,         /*    61    = equal sign                              */
    62,         /*    62    > greater-than sign                       */
    63,         /*    63    ? question mark                           */
    0,          /*    64    @ commercial at sign                      */
    65,         /*    65    A uppercase A                             */
    66,         /*    66    B uppercase B                             */
    67,         /*    67    C uppercase C                             */
    68,         /*    68    D uppercase D                             */
    69,         /*    69    E uppercase E                             */
    70,         /*    70    F uppercase F                             */
    71,         /*    71    G uppercase G                             */
    72,         /*    72    H uppercase H                             */
    73,         /*    73    I uppercase I                             */
    74,         /*    74    J uppercase J                             */
    75,         /*    75    K uppercase K                             */
    76,         /*    76    L uppercase L                             */
    77,         /*    77    M uppercase M                             */
    78,         /*    78    N uppercase N                             */
    79,         /*    79    O uppercase O                             */
    80,         /*    80    P uppercase P                             */
    81,         /*    81    Q uppercase Q                             */
    82,         /*    82    R uppercase R                             */
    83,         /*    83    S uppercase S                             */
    84,         /*    84    T uppercase T                             */
    85,         /*    85    U uppercase U                             */
    86,         /*    86    V uppercase V                             */
    87,         /*    87    W uppercase W                             */
    88,         /*    88    X uppercase X                             */
    89,         /*    89    Y uppercase Y                             */
    90,         /*    90    Z uppercase Z                             */
    60+256,     /*    91    [ left square bracket                     */
    47+256,     /*    92    \ backslash                               */
    62+256,     /*    93    ] right square bracket                    */
    20+256,     /*    94    ^ circumflex accent                       */
    17,         /*    95    _ underscore                              */
    -39,        /*    96    ` back apostrophe                         */
    97,         /*    97    a lowercase a                             */
    98,         /*    98    b lowercase b                             */
    99,         /*    99    c lowercase c                             */
    100,        /*   100    d lowercase d                             */
    101,        /*   101    e lowercase e                             */
    102,        /*   102    f lowercase f                             */
    103,        /*   103    g lowercase g                             */
    104,        /*   104    h lowercase h                             */
    105,        /*   105    i lowercase i                             */
    106,        /*   106    j lowercase j                             */
    107,        /*   107    k lowercase k                             */
    108,        /*   108    l lowercase l                             */
    109,        /*   109    m lowercase m                             */
    110,        /*   110    n lowercase n                             */
    111,        /*   111    o lowercase o                             */
    112,        /*   112    p lowercase p                             */
    113,        /*   113    q lowercase q                             */
    114,        /*   114    r lowercase r                             */
    115,        /*   115    s lowercase s                             */
    116,        /*   116    t lowercase t                             */
    117,        /*   117    u lowercase u                             */
    118,        /*   118    v lowercase v                             */
    119,        /*   119    w lowercase w                             */
    120,        /*   120    x lowercase x                             */
    121,        /*   121    y lowercase y                             */
    122,        /*   122    z lowercase z                             */
    40+256,     /*   123    { left brace                              */
    64+256,     /*   124    | vertical bar                            */
    41+256,     /*   125    } right brace                             */
    61+256,     /*   126    ~ tilde accent                            */
    NPC7,       /*   127      delete [DEL]                            */
    NPC7,       /*   128                                              */
    NPC7,       /*   129                                              */
    -39,        /*   130      low left rising single quote            */
    -102,       /*   131      lowercase italic f                      */
    -34,        /*   132      low left rising double quote            */
    NPC7,       /*   133      low horizontal ellipsis                 */
    NPC7,       /*   134      dagger mark                             */
    NPC7,       /*   135      double dagger mark                      */
    NPC7,       /*   136      letter modifying circumflex             */
    NPC7,       /*   137      per thousand (mille) sign               */
    -83,        /*   138      uppercase S caron or hacek              */
    -39,        /*   139      left single angle quote mark            */
    -214,       /*   140      uppercase OE ligature                   */
    NPC7,       /*   141                                              */
    NPC7,       /*   142                                              */
    NPC7,       /*   143                                              */
    NPC7,       /*   144                                              */
    -39,        /*   145      left single quotation mark              */
    -39,        /*   146      right single quote mark                 */
    -34,        /*   147      left double quotation mark              */
    -34,        /*   148      right double quote mark                 */
    -42,        /*   149      round filled bullet                     */
    -45,        /*   150      en dash                                 */
    -45,        /*   151      em dash                                 */
    -39,        /*   152      small spacing tilde accent              */
    NPC7,       /*   153      trademark sign                          */
    -115,       /*   154      lowercase s caron or hacek              */
    -39,        /*   155      right single angle quote mark           */
    -111,       /*   156      lowercase oe ligature                   */
    NPC7,       /*   157                                              */
    NPC7,       /*   158                                              */
    -89,        /*   159      uppercase Y dieresis or umlaut          */
    -32,        /*   160      non-breaking space                      */
    64,         /*   161    ¡ inverted exclamation mark               */
    -99,        /*   162    ¢ cent sign                               */
    1,          /*   163    £ pound sterling sign                     */
    36,         /*   164    ¤ general currency sign                   */
    3,          /*   165    ¥ yen sign                                */
    -33,        /*   166    ¦ broken vertical bar                     */
    95,         /*   167    § section sign                            */
    -34,        /*   168    ¨ spacing dieresis or umlaut              */
    NPC7,       /*   169    © copyright sign                          */
    NPC7,       /*   170    ª feminine ordinal indicator              */
    -60,        /*   171    « left (double) angle quote               */
    NPC7,       /*   172    ¬ logical not sign                        */
    -45,        /*   173    ­ soft hyphen                             */
    NPC7,       /*   174    ® registered trademark sign               */
    NPC7,       /*   175    ¯ spacing macron (long) accent            */
    NPC7,       /*   176    ° degree sign                             */
    NPC7,       /*   177    ± plus-or-minus sign                      */
    -50,        /*   178    ² superscript 2                           */
    -51,        /*   179    ³ superscript 3                           */
    -39,        /*   180    ´ spacing acute accent                    */
    -117,       /*   181    µ micro sign                              */
    NPC7,       /*   182    ¶ paragraph sign, pilcrow sign            */
    NPC7,       /*   183    · middle dot, centered dot                */
    NPC7,       /*   184    ¸ spacing cedilla                      */
    -49,        /*   185    ¹ superscript 1                           */
    NPC7,       /*   186    º masculine ordinal indicator             */
    -62,        /*   187    » right (double) angle quote (guillemet)  */
    NPC7,       /*   188    ¼ fraction 1/4                            */
    NPC7,       /*   189    ½ fraction 1/2                            */
    NPC7,       /*   190    ¾ fraction 3/4                            */
    96,         /*   191    ¿ inverted question mark                  */
    -65,        /*   192    À uppercase A grave                       */
    -65,        /*   193    Á uppercase A acute                       */
    -65,        /*   194    Â uppercase A circumflex                  */
    -65,        /*   195    Ã uppercase A tilde                       */
    91,         /*   196    Ä     *31,                                */        
    -31,        /*   202    Ê upperc*/
    -31,        /*   203    Ë uppercase E dieresis or umlaut          */
    -73,        /*   204    Ì uppercase I grave                       */
    -73,        /*   206    Î uppercase I acute                  */
    -73,        /*   207    Ï uppercase I dieresis or umlaut          */
    -68,        /*   208    Ð uppercase ETH                           */
    93,         /*   209    Ñ uppercase N tilde                       */
    -79,        /*   210    Ò uppercase O grave                       */
    -79,        /*   211    Ó uppercase O acute                       */
    -79,        /*   212    Ô uppercase O circumflex                  */
    -79,        /*   213    Õ uppercase O tilde                       */
    92,         /*   214    Ö uppercase O dieresis or umlaut          */
    -42,        /*   215    × multiplication sign                     */

    -85,        /*   219    Û uppercase U circumflex                  */
    94,         /*   220    Ü uppercase U dieresis or umlaut          */
    -89,        /*   221    Ý uppercase Y acute                       */
    NPC7,       /*   222    Þ uppercase THORN                         */
    30,         /*   223    ß lowercase sharp s, sz ligature          */
    127,        /*   224    à lowercase a grave                       */
    -97,        /*   225    á lowercase a acute                       */
    -97,        /*   226    â lowercase a circumflex                  */
    -97,        /*   227    ã lowercase a tilde                       */
    123,        /*   228    ä lowercase a dieresis or umlaut          */
    15,         /*   229    å lowercase a ring                        */
    29,         /*   230    æ lowercase ae ligature                   */
    -9,         /*   231    ç lowercase c cedilla                     */
    4,          /*   232    è lowercase e grave                       */
    5,          /*   233    é lowercase e acute                       */
    -101,       /*   234    ê lowercase e circumflex                  */
    -101,       /*   235    ë lowercase e dieresis or umlaut          */
    7,          /*   236    ì lowercase i grave                       */
    7,          /*   237    í lowercase i acute                       */
    -105,       /*   238    î lowercase i circumflex                  */
    -105,       /*   239    ï lowercase i dieresis or umlaut          */
    NPC7,       /*   240    ð lowercase eth                           */
    125,        /*   241    ñ lowercase n tilde                       */
    8,          /*   242    ò lowercase o grave                       */
    -111,       /*   243    ó lowercase o acute                       */
    -111,       /*   244    ô lowercase o circumflex                  */
    -111,       /*   245    õ lowercase o tilde                       */
    124,        /*   246    ö lowercase o dieresis or umlaut          */
    -47,        /*   247    ÷ division sign                           */
    12,         /*   248    ø lowercase o slash                       */
    6,          /*   249    ù lowercase u grave                       */
    -117,       /*   250    ú lowercase u acute                       */
    -117,       /*   251    û lowercase u circumflex                  */
    126,        /*   252    ü lowercase u dieresis or umlaut          */
    -121,       /*   253    ý lowercase y acute                       */
    NPC7,       /*   254    þ lowercase thorn                         */
    -121        /*   255    ÿ lowercase y dieresis or umlaut          */
};



/****************************************************************************
   This lookup table converts from the 7 bit "default alphabet" as 
    defined in ETSI GSM 03.38 to a standard ISO-8859-1 8-bit ASCII.  
    
    Some characters in the 7-bit alphabet does not exist in the ISO
    character set, they are replaced by the NPC8-character.
    
    If the character is decimal 27 (ESC) the following character have
    a special meaning and must be handled separately.
****************************************************************************/

int lookup_ascii7to8[]={
    64,         /*  0      @  COMMERCIAL AT                           */      
    163,        /*  1      £  POUND SIGN                              */      
    36,         /*  2      $  DOLLAR SIGN                             */      
    165,        /*  3      ¥  YEN SIGN                                */      
    232,        /*  4      è  LATIN SMALL LETTER E WITH GRAVE         */      
    233,        /*  5      é  LATIN SMALL LETTER E WITH ACUTE         */      
    249,        /*  6      ù  LATIN SMALL LETTER U WITH GRAVE         */      
    236,        /*  7      ì  LATIN SMALL LETTER I WITH GRAVE         */      
    242,        /*  8      ò  LATIN SMALL LETTER O WITH GRAVE         */      
    199,        /*  9      Ç  LATIN CAPITAL LETTER C WITH CEDILLA     */      
    10,         /*  10        LINE FEED                               */      
    216,        /*  11     Ø  LATIN CAPITAL LETTER O WITH STROKE      */      
    248,        /*  12     ø  LATIN SMALL LETTER O WITH STROKE        */      
    13,         /*  13        CARRIAGE RETURN                         */      
    197,        /*  14     APITAL LETxTER A WITH RING                 */      
    229,        /*  15     å  LATIN SMALL LETTER A WITH RING ABOVE    */   
     NPC8,       /*  16        GREEK CAPITAL LETTER DELTA             */
    95,         /*  17     _  LOW LINE                                */      
    NPC8,       /*  18        GREEK CAPITAL LETTER PHI                */
    NPC8,       /*  19        GREEK CAPITAL LETTER GAMMA              */
    NPC8,       /*  20        GREEK CAPITAL LETTER LAMBDA             */
    NPC8,       /*  21        GREEK CAPITAL LETTER OMEGA              */
    NPC8,       /*  22        GREEK CAPITAL LETTER PI                 */
    NPC8,       /*  23        GREEK CAPITAL LETTER PSI                */
    NPC8,       /*  24        GREEK CAPITAL LETTER SIGMA              */
    NPC8,       /*  25        GREEK CAPITAL LETTER THETA              */
    NPC8,       /*  26        GREEK CAPITAL LETTER XI                 */
    27,         /*  27        ESCAPE TO EXTENSION TABLE               */
    198,        /*  28     Æ  LATIN CAPITAL LETTER AE                 */                 
    230,        /*  29     æ  LATIN SMALL LETTER AE                   */      
    223,        /*  30     ß  LATIN SMALL LETTER SHARP S (German)     */      
    201,        /*  31     É  LATIN CAPITAL LETTER E WITH ACUTE       */      
    32,         /*  32        SPACE                                   */       
    33,         /*  33     !  EXCLAMATION MARK                        */       
    34,         /*  34     "  QUOTATION MARK                          */       
    35,         /*  35     #  NUMBER SIGN                             */       
    164,        /*  36     ¤  CURRENCY SIGN                           */       
    37,         /*  37     %  PERCENT SIGN                            */       
    38,         /*  38     &  AMPERSAND                               */       
    39,         /*  39     '  APOSTROPHE                              */       
    40,         /*  40     (  LEFT PARENTHESIS                        */       
    41,         /*  41     )  RIGHT PARENTHESIS                       */       
    42,         /*  42     *  ASTERISK                                */       
    43,         /*  43     +  PLUS SIGN                               */       
    44,         /*  44     ,  COMMA                                   */       
    45,         /*  45     -  HYPHEN-MINUS                            */       
    46,         /*  46     .  FULL STOP                               */       
    47,         /*  47     /  SOLIDUS (SLASH)                         */       
    48,         /*  48     0  DIGIT ZERO                              */       
    49,         /*  49     1  DIGIT ONE                               */       
    50,         /*  50     2  DIGIT TWO                               */       
    51,         /*  51     3  DIGIT THREE                             */       
    52,         /*  52     4  DIGIT FOUR                              */       
    53,         /*  53     5  DIGIT FIVE                              */       
    54,         /*  54     6  DIGIT SIX                               */       
    55,         /*  55     7  DIGIT SEVEN                             */       
    56,         /*  56     8  DIGIT EIGHT                             */       
    57,         /*  57     9  DIGIT NINE                              */       
    58,         /*  58     :  COLON                                   */       
    59,         /*  59     ;  SEMICOLON                               */       
    60,         /*  60     <  LESS-THAN SIGN                          */       
    61,         /*  61     =  EQUALS SIGN                             */       
    62,         /*  62     >  GREATER-THAN SIGN                       */                                       
    63,         /*  63     ?  QUESTION MARK                           */       
    161,        /*  64     ¡  INVERTED EXCLAMATION MARK               */       
    65,         /*  65     A  LATIN CAPITAL LETTER A                  */       
    66,         /*  66     B  LATIN CAPITAL LETTER B                  */       
    67,         /*  67     C  LATIN CAPITAL LETTER C                  */       
    68,         /*  68     D  LATIN CAPITAL LETTER D                  */       
    69,         /*  69     E  LATIN CAPITAL LETTER E                  */       
    70,         /*  70     F  LATIN CAPITAL LETTER F                  */       
    71,         /*  71     G  LATIN CAPITAL LETTER G                  */       
    72,         /*  72     H  LATIN CAPITAL LETTER H                  */       
    73,         /*  73     I  LATIN CAPITAL LETTER I                  */       
    74,         /*  74     J  LATIN CAPITAL LETTER J                  */       
    75,         /*  75     K  LATIN CAPITAL LETTER K                  */       
    76,         /*  76     L  LATIN CAPITAL LETTER L                  */       
    77,         /*  77     M  LATIN CAPITAL LETTER M                  */       
    78,         /*  78     N  LATIN CAPITAL LETTER N                  */       
    79,         /*  79     O  LATIN CAPITAL LETTER O                  */       
    80,         /*  80     P  LATIN CAPITAL LETTER P                  */       
    81,         /*  81     Q  LATIN CAPITAL LETTER Q                  */       
    82,         /*  82     R  LATIN CAPITAL LETTER R                  */       
    83,         /*  83     S  LATIN CAPITAL LETTER S                  */       
    84,         /*  84     T  LATIN CAPITAL LETTER T                  */       
    85,         /*  85     U  LATIN CAPITAL LETTER U                  */       
    86,         /*  86     V  LATIN CAPITAL LETTER V                  */       
    87,         /*  87     W  LATIN CAPITAL LETTER W                  */       
    88,         /*  88     X  LATIN CAPITAL LETTER X                  */       
    89,         /*  89     Y  LATIN CAPITAL LETTER Y                  */       
    90,         /*  90     Z  LATIN CAPITAL LETTER Z                  */       
    196,        /*  91     Ã LATIN CAPITAL LETTER O WITH DIAERESIS   */
     214,        /*  92     Ã LATIN CAPITAL LETTER O WITH DIAERESIS   */
    209,        /*  93     Ã LATIN CAPITAL LETTER N WITH TILDE       */
    220,        /*  94     Ü  LATIN CAPITAL LETTER U WITH DIAERESIS   */       
    167,        /*  95     §  SECTION SIGN                            */       
    191,        /*  96     ¿  INVERTED QUESTION MARK                  */       
    97,         /*  97     a  LATIN SMALL LETTER A                    */       
    98,         /*  98     b  LATIN SMALL LETTER B                    */       
    99,         /*  99     c  LATIN SMALL LETTER C                    */       
    100,        /*  100    d  LATIN SMALL LETTER D                    */       
    101,        /*  101    e  LATIN SMALL LETTER E                    */       
    102,        /*  102    f  LATIN SMALL LETTER F                    */                                       
    103,        /*  103    g  LATIN SMALL LETTER G                    */       
    104,        /*  104    h  LATIN SMALL LETTER H                    */       
    105,        /*  105    i  LATIN SMALL LETTER I                    */       
    106,        /*  106    j  LATIN SMALL LETTER J                    */       
    107,        /*  107    k  LATIN SMALL LETTER K                    */       
    108,        /*  108    l  LATIN SMALL LETTER L                    */       
    109,        /*  109    m  LATIN SMALL LETTER M                    */       
    110,        /*  110    n  LATIN SMALL LETTER N                    */       
    111,        /*  111    o  LATIN SMALL LETTER O                    */       
    112,        /*  112    p  LATIN SMALL LETTER P                    */       
    113,        /*  113    q  LATIN SMALL LETTER Q                    */       
    114,        /*  114    r  LATIN SMALL LETTER R                    */       
    115,        /*  115    s  LATIN SMALL LETTER S                    */       
    116,        /*  116    t  LATIN SMALL LETTER T                    */       
    117,        /*  117    u  LATIN SMALL LETTER U                    */       
    118,        /*  118    v  LATIN SMALL LETTER V                    */       
    119,        /*  119    w  LATIN SMALL LETTER W                    */       
    120,        /*  120    x  LATIN SMALL LETTER X                    */       
    121,        /*  121    y  LATIN SMALL LETTER Y                    */       
    122,        /*  122    z  LATIN SMALL LETTER Z                    */       
    228,        /*  123    ä  LATIN SMALL LETTER A WITH DIAERESIS     */       
    246,        /*  124    ö  LATIN SMALL LETTER O WITH DIAERESIS     */       
    241,        /*  125    ñ  LATIN SMALL LETTER N WITH TILDE         */       
    252,        /*  126    ü  LATIN SMALL LETTER U WITH DIAERESIS     */       
    224         /*  127    à  LATIN SMALL LETTER A WITH GRAVE         */         

/*  The double bytes below must be handled separately after the
    table lookup.
    
    12             27 10      FORM FEED                                       
    94             27 20   ^  CIRCUMFLEX ACCENT                               
    123            27 40   {  LEFT CURLY BRACKET                              
    125            27 41   }  RIGHT CURLY BRACKET                             
    92             27 47   \  REVERSE SOLIDUS (BACKSLASH)                     
    91             27 60   [  LEFT SQUARE BRACKET                             
    126            27 61   ~  TILDE                                           
    93             27 62   ]  RIGHT SQUARE BRACKET                            
    124            27 64   |  VERTICAL BAR                             */

};

/************************************************************************
 * Use a lookup table to convert from the 7-bit default alphabet
 * used by SMS to an ISO-8859-1 ASCII string. 
 *  
 *  *a7bit   An array of the 7-bit 'string' to convert
 *
 *  length   The length of the a7bit-array
 *
 *  **ascii  A pointer to the string that the result is stored in,
 *           the space is malloced by this function
 *
 *  Returns the length of the ascii-string
 *
 *  Note:  The ascii-string must be free()'ed by te caller
 ************************************************************************/

static 
int convert_7bit_to_ascii(char *a7bit, int length, char **ascii) 
{
   int     r;
   int     w;

   /* Allocate sufficient memory for the result string */
   *ascii=(char *)malloc(length*2+1);
   memset(*ascii, 0, length*2+1);

   w=0;
   for (r=0; r<length; r++) 
   {
      if ((lookup_ascii7to8[(unsigned char)a7bit[r]])!=27) 
      {
          (*ascii)[w++]=lookup_ascii7to8[(unsigned char)a7bit[r]];
      } 
      else 
      {
         /* If we're escaped then the next byte have a special meaning. */
         r++;
          switch (a7bit[r]) 
          {
              case 10:
                    (*ascii)[w++]=12;
                    break;
              case 20:
                    (*ascii)[w++]='^';
                    break;
              case 40:
                    (*ascii)[w++]='{';
                    break;
              case 41:
                    (*ascii)[w++]='}';
                    break;
              case 47:
                    (*ascii)[w++]='\\';
                    break;
              case 60:
                    (*ascii)[w++]='[';
                    break;
              case 61:
                    (*ascii)[w++]='~';
                    break;

              case 62:
                    (*ascii)[w++]=']';
                    break;
              case 64:
                    (*ascii)[w++]='|';
                    break;
              default:
                    (*ascii)[w++]=NPC8;
                    break;
          }
      }
   }

    /* Terminate the result string and realloc to the correct size */
    (*ascii)[w]=0;
    *ascii=(char *)realloc(*ascii,w+1);

    return w;
}    
    
/*****************************************************************
 * Use a lookup table to convert from an ISO-8859-1 string to 
 * the 7-bit default alphabet used by SMS. 
 *  
 *  *scii   The string to convert
 *
 *  **a7bit  A pointer to the array that the result is stored in,
 *           the space is malloced by this function
 *
 *  Returns the length of the a7bit-array
 *
 *  Note:  The a7bit-array must be free()'ed by te caller
 *****************************************************************/

static int convert_ascii_to_7bit(char *ascii, char **a7bit) 
{
   int r;
   int w;
   r=0;
   w=0;

   /* Allocate sufficient memory for the result string */
   *a7bit=(char *)malloc(strlen(ascii)*2+1);
   memset(*a7bit, 0, strlen(ascii)*2+1);

   while (ascii[r]!=0) 
   {
       if ((lookup_ascii8to7[(unsigned char)ascii[r]])<256) 
       {
           (*a7bit)[w++]=abs(lookup_ascii8to7[(unsigned char)ascii[r++]]);
       } 
       else
       {
          (*a7bit)[w++]=27;
          (*a7bit)[w++]=lookup_ascii8to7[(unsigned char)ascii[r++]]-256;
       }
   }
    
   /* Realloc the result array to the correct size */
   (*a7bit)[w]=0;
   *a7bit=(char *)realloc(*a7bit,w+1);

    return w;
}



static void
SevenBitSet(ITS_OCTET *array, ITS_USHORT offset,
                  ITS_OCTET value)
{
    ITS_USHORT bit, byte;
    ITS_OCTET himask, lomask;

    byte = (offset * 7) / 8;
    bit = (offset * 7) % 8;
    lomask = 0x7FU << bit;
    himask = 0x7FU >> (8 - bit);

    array[byte] &= ~lomask;
    array[byte] |= (value << bit) & lomask;
    if (bit != 0 && bit != 1)
    {
        array[byte+1] &= ~himask;
        array[byte+1] |= (value >> (8 - bit)) & himask;
    }
}

static ITS_OCTET
SevenBitGet(ITS_OCTET *array, ITS_USHORT offset)
{
   ITS_USHORT bit, byte;
   ITS_OCTET himask, lomask;
   ITS_OCTET value = 0;

   byte = (offset * 7) / 8;
   bit = (offset * 7) % 8;
   lomask = 0x7FU << bit;
   himask = 0x7FU >> (8 - bit);

   value = (array[byte] & lomask) >> bit;
   if (bit != 0 && bit != 1)
   {
       value |= (array[byte+1] & himask) << (8 - bit);
   }

   return (value);
}


MapUserInfo_SMSSubmit::MapUserInfo_SMSSubmit ()
{
    Initialize ();
}

MapUserInfo_SMSSubmit::MapUserInfo_SMSSubmit (ITS_OCTET* usrInfo, ITS_USHORT usrInfoLen)
{
    Initialize ();
    Decode (usrInfo, usrInfoLen);
}

void MapUserInfo_SMSSubmit :: Initialize ()
{
    msgTypeInd_ = 0;
    rejDup_ = ITS_FALSE;
    valPerFormat_ = 0;
    repPath_ = ITS_FALSE;
    usrDtHdrInd_ = ITS_FALSE;
    statRepReq_ = ITS_FALSE;
    msgRef_ = 0;
    destAddrLen_ = 0;
    destAddrType_ = 0;
    destAddr_ = "";
    protId_ = 0;
    dataCodeScheme_ = 0;
    memset (valPeriod_, MAX_VALIDITY_PERIOD_LEN, 0);
    usrDataStrLen_ = 0;
    memset(usrDataStr_, MAX_USER_DATA_LEN, 0);
}

void 
MapUserInfo_SMSSubmit::SetMessageIndicator (ITS_OCTET msgTypeInd)
{
    msgTypeInd_ = msgTypeInd;
}

ITS_OCTET 
MapUserInfo_SMSSubmit::GetMessageIndicator () const
{
    return msgTypeInd_;
}

void 
MapUserInfo_SMSSubmit::SetRejectDuplicates (ITS_BOOLEAN rejDup)
{
    rejDup_ = rejDup;
}

ITS_BOOLEAN 
MapUserInfo_SMSSubmit::GetRejectDuplicates () const
{
    return rejDup_;
}

void 
MapUserInfo_SMSSubmit::SetValidityPeriodFormat (ITS_OCTET valPerFormat)
{
    valPerFormat_ = valPerFormat;
}

ITS_OCTET 
MapUserInfo_SMSSubmit::GetValidityPeriodFormat () const
{
    return valPerFormat_;
}

void 
MapUserInfo_SMSSubmit::SetReplyPath (ITS_BOOLEAN repPath)
{
    repPath_ = repPath;
}

ITS_BOOLEAN 
MapUserInfo_SMSSubmit::GetReplyPath () const
{
    return repPath_;
}

void
MapUserInfo_SMSSubmit::SetUserDataHdrInd (ITS_BOOLEAN usrDataHdrInd)
{
    usrDtHdrInd_ = usrDataHdrInd;
}

ITS_BOOLEAN 
MapUserInfo_SMSSubmit::GetUserDataHdrInd () const
{
    return usrDtHdrInd_;
}

void 
MapUserInfo_SMSSubmit::SetStatusReportRequest (ITS_BOOLEAN statRepReq)
{
    statRepReq_ = statRepReq;
}

ITS_BOOLEAN 
MapUserInfo_SMSSubmit::GetStatusReportRequest () const
{
    return statRepReq_;
}

void 
MapUserInfo_SMSSubmit::SetMsgReference (ITS_OCTET msgRef)
{
    msgRef_ = msgRef;
}

ITS_OCTET 
MapUserInfo_SMSSubmit::GetMsgReference () const
{
    return msgRef_;
}

void 
MapUserInfo_SMSSubmit::SetDestAddr (ITS_OCTET destAddrLen,
                                    ITS_OCTET destAddrType,
                                    std::string destAddr)
{
    destAddrLen_ = destAddrLen;
    destAddrType_ = destAddrType;
    destAddr_ = destAddr;
}

void 
MapUserInfo_SMSSubmit::GetDestAddr (ITS_OCTET& destAddrLen,
             ITS_OCTET& destAddrType,
             std::string& destAddr)
{
    destAddrLen = destAddrLen_;
    destAddrType = destAddrType_;
    destAddr = destAddr_;
}

void 
MapUserInfo_SMSSubmit::SetProtocolId (ITS_OCTET protId)
{
    protId_ = protId;
}

ITS_OCTET 
MapUserInfo_SMSSubmit::GetProtocolId () const
{
    return protId_;
}

void 
MapUserInfo_SMSSubmit::SetDataCodingScheme (ITS_OCTET dataCodeScheme)
{
    dataCodeScheme_ = dataCodeScheme;
}

ITS_OCTET 
MapUserInfo_SMSSubmit::GetDataCodingScheme () const
{
    return dataCodeScheme_;
}

void 
MapUserInfo_SMSSubmit::SetValidityPeriod (ITS_OCTET* valPeriod)
{
    if (valPeriod == NULL || valPeriod_ == NULL) return;

    switch (valPerFormat_)
    {
        case 2:
            valPeriod_[0] = valPeriod[0];
            break;
        case 1:
        case 3:
            memcpy (valPeriod_, valPeriod, MAX_VALIDITY_PERIOD_LEN);
            break;
    }
}

void 
MapUserInfo_SMSSubmit::GetValidityPeriod (ITS_OCTET* valPeriod) const
{
    if (valPeriod == NULL || valPeriod_ == NULL) return;

    switch (valPerFormat_)
    {
        case 2:
            valPeriod[0] = valPeriod_[0];
            break;
        case 1:
        case 3:
            memcpy (valPeriod, valPeriod_, MAX_VALIDITY_PERIOD_LEN);
            break;
    }
}

ITS_INT
MapUserInfo_SMSSubmit::SetUserData (ITS_OCTET* usrData, ITS_UINT usrDataLen)
{
    if (usrDataLen && usrData)
    {
        memcpy (usrDataStr_, usrData, usrDataLen);
        usrDataStrLen_ = usrDataLen;
        return ITS_SUCCESS;
    }

    return ITS_ENULLPTR;
}

ITS_INT
MapUserInfo_SMSSubmit::GetUserData (ITS_OCTET* usrData, ITS_UINT* usrDataLen)
{
    if (*usrDataLen >= usrDataStrLen_)
    {
        memcpy(usrData, usrDataStr_, usrDataStrLen_);
        *usrDataLen = usrDataStrLen_;
        return ITS_SUCCESS;
    }

    return usrDataStrLen_;
}

int 
MapUserInfo_SMSSubmit::Encode (ITS_OCTET* data, ITS_USHORT& dataLen)
{
    ITS_OCTET buf[255];
    ITS_USHORT bufIndex = 0;
    memset (buf, 0 , 255);
   
    buf[bufIndex] = (msgTypeInd_ & 0x03); 
   
    if (rejDup_)
    {
        buf[bufIndex] |= 0x04;
    }

    buf[bufIndex] |= ((valPerFormat_ & 0x03) << 3);

    if (statRepReq_)
    {
        buf [bufIndex] |= 0x20; 
    }
 
    if (usrDtHdrInd_)
    {
        buf [bufIndex] |= 0x40; 
    }

    if (repPath_)
    {
        buf [bufIndex] |= 0x80;
    }

    bufIndex++;
    buf [bufIndex] = (msgRef_ & 0xff); bufIndex++;
    buf [bufIndex] = (destAddrLen_ & 0xff); bufIndex++; 
    buf [bufIndex] = (destAddrType_ & 0xff); bufIndex++;

    int len = strlen (destAddr_.c_str());

    if (len > MAX_DEST_ADDR_LEN) 
    {
        return -1;
    }

    ITS_USHORT tempLen = (len % 2)? (len - 1) : len;
   
    ITS_CHAR* temp = (ITS_CHAR*)destAddr_.c_str(); 
    ITS_OCTET val = 0;
    int i = 0;
    for ( ; i < tempLen; )
    {
        val = ((SetTBCDCharacter(temp[i])) & 0x0f) | 
                  (((SetTBCDCharacter(temp[i+1])) & 0x0f) << 4);
     
        buf [bufIndex] = (val & 0xff); bufIndex++;
        i += 2;
    }

    if (len % 2) 
    {
        val = SetTBCDCharacter(temp[i]) & 0x0f;
        val |= 0xf0;
        buf [bufIndex] = (val & 0xff); bufIndex++;
    }

    buf [bufIndex] = protId_; bufIndex++;

    buf [bufIndex] = dataCodeScheme_; bufIndex++;

    switch (valPerFormat_)
    {
        case 2:
            buf [bufIndex] = valPeriod_[0]; bufIndex++;
            break;
        case 1:
        case 3:
            memcpy(&buf [bufIndex], valPeriod_, MAX_VALIDITY_PERIOD_LEN); 
            bufIndex += MAX_VALIDITY_PERIOD_LEN;
            break;
    }

    if (usrDataStrLen_ && usrDataStr_)
    {
        memcpy (&buf [bufIndex], usrDataStr_, usrDataStrLen_);
        bufIndex += usrDataStrLen_;
    }

    if (dataLen >= bufIndex)
    {
        memcpy (data, buf, bufIndex);
        dataLen = bufIndex;
        return ITS_SUCCESS;
    }
    else
    {
        return bufIndex;
    }
}

int 
MapUserInfo_SMSSubmit::Decode (ITS_OCTET* data, ITS_USHORT dataLen)
{
    ITS_USHORT bufIndex = 0;
    Initialize();

    msgTypeInd_ = data[bufIndex] & 0x03;
    rejDup_ = (data[bufIndex] & 0x04)? ITS_TRUE : ITS_FALSE;
    valPerFormat_ = (data[bufIndex] & 0x18) >> 3;
    repPath_ = (data[bufIndex] & 0x80)? ITS_TRUE : ITS_FALSE;
    usrDtHdrInd_ = (data[bufIndex] & 0x40)? ITS_TRUE : ITS_FALSE;
    statRepReq_ = (data[bufIndex] & 0x20)? ITS_TRUE : ITS_FALSE;

    bufIndex++;

    msgRef_ = data[bufIndex]; bufIndex++;
    destAddrLen_ = data[bufIndex]; bufIndex++;
    destAddrType_ = data[bufIndex]; bufIndex++;

    destAddr_ = "";

    ITS_USHORT templen = (destAddrLen_ % 2)? (destAddrLen_ - 1) : destAddrLen_;
    char valch = 0;
    for (int i = 0; i < templen; i+=2)
    {
        destAddr_ += GetTBCDCharacter (data[bufIndex] & 0x0f);
        destAddr_ += GetTBCDCharacter ((data[bufIndex] & 0xf0) >> 4);        
        bufIndex++;
    }
  
    if (destAddrLen_ % 2)
    {
        destAddr_ += GetTBCDCharacter (data[bufIndex] & 0x0f);
        bufIndex++;
    } 

    protId_ = data[bufIndex]; bufIndex++;
    dataCodeScheme_ = data[bufIndex]; bufIndex++;

    switch (valPerFormat_)
    {
        case 2:
            valPeriod_[0] = data[bufIndex]; bufIndex++;
            break;
        case 1:
        case 3:
            memcpy (valPeriod_, &data[bufIndex], MAX_VALIDITY_PERIOD_LEN);
            bufIndex += MAX_VALIDITY_PERIOD_LEN;
            break;
    }

    if (dataLen > bufIndex)
    {
        usrDataStrLen_ = dataLen - bufIndex;
        memcpy (usrDataStr_, &data[bufIndex], usrDataStrLen_);
    }

    return ITS_SUCCESS;
}

void
MapUserInfo_SMSSubmit::Print()
{
    printf ("\nmsgTypeInd : %d\n",msgTypeInd_);

    if (rejDup_)
        printf ("rejDup : ITS_TRUE\n");
    else
        printf ("rejDup : ITS_FALSE\n");

    printf ("valPerFormat : %d\n",valPerFormat_);

    if (repPath_)
         printf ("repPath : ITS_TRUE\n");
    else
         printf ("repPath : ITS_FALSE\n");

    if (usrDtHdrInd_)
        printf ("usrDtHdrInd : ITS_TRUE\n");
    else
        printf ("usrDtHdrInd : ITS_FALSE\n");

    if (statRepReq_)
        printf ("statRepReq : ITS_TRUE\n");
    else
        printf ("statRepReq : ITS_FALSE\n");

    printf ("msgRef : %d\n",msgRef_);

    printf ("destAddrLen : %d\n",destAddrLen_);

    printf ("destAddrType : %d\n",destAddrType_);
    printf ("\tType of Number : %d\n",GET_TYPE_OF_NUMBER(destAddrType_));
    printf ("\tNumbering Plan : %d\n",GET_NUMBERING_PLAN(destAddrType_));

    printf ("destAddr : %s\n",destAddr_.c_str());

    printf ("protId : %d\n",protId_);

    printf ("dataCodeScheme : %d\n",dataCodeScheme_);
    printf ("\tCoding Group : %d\n",GET_CODING_GROUP(dataCodeScheme_));
    printf ("\tAlphabet Used : %d\n",GET_ALPHABET_USED(dataCodeScheme_));
    printf ("\tMessage Class : %d\n",GET_MSG_CLASS(dataCodeScheme_));

    printf ("Validity Period : ");

    if (valPerFormat_)
    {
         int vplen = (valPerFormat_ == 2)? 1 : 7;
         for (int i = 0; i < vplen; i++) 
            printf ("%02x ",valPeriod_[i]);
         printf("\n");
    }

    ValidityPeriod vperiod;

    CalculateValidityPeriod(valPerFormat_, valPeriod_, &vperiod);
    printf ("Validity Period Value : \n");
    printf ("Day         : %02x\n",vperiod.day & 0xff);
    printf ("month       : %02x\n",vperiod.month);
    printf ("year        : %02x\n",vperiod.year);
    printf ("hour        : %02x\n",vperiod.hour);
    printf ("minute      : %02x\n",vperiod.minute);
    printf ("second      : %02x\n",vperiod.second);
    printf ("timezone    : %02x\n",vperiod.timezone);
    printf ("TP-VP value : %d secs\n",vperiod.tpvpValue);

    ITS_OCTET str[255];
    ITS_UINT strLen = 255;
    GetUserData(str, &strLen);

    printf ("\nUser data : \n");
    for (int i = 0; i < strLen; i++)
        printf ("%02x ", str[i]);
    printf("\n");
}

MapUserInfo_SMSDeliver::MapUserInfo_SMSDeliver ()
{
    Initialize ();
}

MapUserInfo_SMSDeliver::MapUserInfo_SMSDeliver (ITS_OCTET* usrInfo, ITS_USHORT usrInfoLen)
{
    Initialize ();
    Decode (usrInfo, usrInfoLen);
}

void MapUserInfo_SMSDeliver :: Initialize ()
{
    msgTypeInd_ = 0;
    moreMsgsToSend_ = ITS_FALSE;
    replyPath_ = ITS_FALSE;
    usrDataHdrInd_ = ITS_FALSE;
    statRepInd_ = ITS_FALSE;
    origAddrLen_ = 0;
    origAddrType_ = 0;
    origAddr_ = "";
    protId_ = 0;
    dataCodeScheme_ = 0;
    memset (srvCenterTS_, MAX_VALIDITY_PERIOD_LEN, 0);
    memset(usrDataStr_, MAX_USER_DATA_LEN, 0);
    usrDataStrLen_ = 0;
}

void
MapUserInfo_SMSDeliver::SetMessageIndicator (ITS_OCTET msgTypeInd)
{
    msgTypeInd_ = msgTypeInd;
}

ITS_OCTET
MapUserInfo_SMSDeliver::GetMessageIndicator () const
{
    return msgTypeInd_;
}

void
MapUserInfo_SMSDeliver::SetMoreMsgsToSend (ITS_BOOLEAN moreMsgsToSend)
{
    moreMsgsToSend_ = moreMsgsToSend;
}

ITS_BOOLEAN
MapUserInfo_SMSDeliver::GetMoreMsgsToSend () const
{
    return moreMsgsToSend_;
}

void
MapUserInfo_SMSDeliver::SetReplyPath (ITS_BOOLEAN repPath)
{
    replyPath_ = repPath;
}

ITS_BOOLEAN
MapUserInfo_SMSDeliver::GetReplyPath () const
{
    return replyPath_;
}

void 
MapUserInfo_SMSDeliver::SetUserDataHdrInd (ITS_BOOLEAN usrDataHdrInd)
{
    usrDataHdrInd_ = usrDataHdrInd;
}

ITS_BOOLEAN
MapUserInfo_SMSDeliver::GetUserDataHdrInd () const
{
    return usrDataHdrInd_;
}

void
MapUserInfo_SMSDeliver::SetStatusReportIndication (ITS_BOOLEAN statRepInd)
{
    statRepInd_ = statRepInd;
}

ITS_BOOLEAN
MapUserInfo_SMSDeliver::GetStatusReportIndication () const
{
    return statRepInd_;
}

void
MapUserInfo_SMSDeliver::SetOrigAddr (ITS_OCTET origAddrLen,
              ITS_OCTET origAddrType,
              std::string origAddr)
{
    origAddrLen_ = origAddrLen;
    origAddrType_ = origAddrType;
    origAddr_ = origAddr;
}

void
MapUserInfo_SMSDeliver::GetOrigAddr (ITS_OCTET& origAddrLen,
             ITS_OCTET& origAddrType,
             std::string& origAddr) const
{
    origAddrLen = origAddrLen_;
    origAddrType = origAddrType_;
    origAddr = origAddr_;
}

void
MapUserInfo_SMSDeliver::SetProtocolId (ITS_OCTET protId)
{
    protId_ = protId;
}

ITS_OCTET
MapUserInfo_SMSDeliver::GetProtocolId () const
{
    return protId_;
}

void
MapUserInfo_SMSDeliver::SetDataCodingScheme (ITS_OCTET dataCodeScheme)
{
    dataCodeScheme_ = dataCodeScheme;
}

ITS_OCTET
MapUserInfo_SMSDeliver::GetDataCodingScheme () const
{
    return dataCodeScheme_;
}

void
MapUserInfo_SMSDeliver::SetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS)
{
    if (srvCenterTS == NULL) return;
  
    memcpy (srvCenterTS_, srvCenterTS, 7);
}

void
MapUserInfo_SMSDeliver::GetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS) const
{
    if (srvCenterTS == NULL) return;
  
    memcpy (srvCenterTS, srvCenterTS_, 7);
}

ITS_INT
MapUserInfo_SMSDeliver::SetUserData (ITS_OCTET* usrData, ITS_UINT usrDataLen)
{
    if (usrDataLen && usrData)
    {
        memcpy (usrDataStr_, usrData, usrDataLen);
        usrDataStrLen_ = usrDataLen;
        return ITS_SUCCESS;
    }

    return ITS_ENULLPTR;
}

ITS_INT
MapUserInfo_SMSDeliver::GetUserData (ITS_OCTET* usrData, ITS_UINT* usrDataLen)
{
    if (*usrDataLen >= usrDataStrLen_)
    {
        memcpy(usrData, usrDataStr_, usrDataStrLen_);
        *usrDataLen = usrDataStrLen_;
        return ITS_SUCCESS;
    }

    return usrDataStrLen_;
}

int
MapUserInfo_SMSDeliver::Encode (ITS_OCTET* data, ITS_USHORT& dataLen)
{
    ITS_OCTET buf[sizeof(MapUserInfo_SMSDeliver) + MAX_ORIG_ADDR_LEN + 1];
    ITS_USHORT bufIndex = 0;

    memset (buf, 0, sizeof(buf));
    buf[bufIndex] = 0;
    buf[bufIndex] = (msgTypeInd_ & 0x03);

    if (moreMsgsToSend_)
    {
        buf[bufIndex] |= 0x04;
    }

    if (replyPath_)
    {
        buf [bufIndex] |= 0x80;
    }

    if (usrDataHdrInd_)
    {
        buf [bufIndex] |= 0x40;
    }

    if (statRepInd_)
    {
        buf [bufIndex] |= 0x20;
    }

    bufIndex++;
    buf [bufIndex] = (origAddrLen_ & 0xff); bufIndex++;
    buf [bufIndex] = (origAddrType_ & 0xff); bufIndex++;

    int len = strlen (origAddr_.c_str());

    if (len > MAX_ORIG_ADDR_LEN)
    {
        return -1;
    }

    if (origAddrType_ == 0xD0)
    {
        char* temp = (char*)origAddr_.c_str();
        char* bit7ascii = NULL;
        len = convert_ascii_to_7bit(temp, &bit7ascii);    
        if (bit7ascii)
        {
            for (int i = 0; i < len; i++)
            {
	        SevenBitSet (&buf [bufIndex], i, bit7ascii[i]);
            }
            free (bit7ascii);
        }
	len = (len * 7);
	bufIndex += (len / 8);

	if (len % 8)
	{
	    bufIndex++;
	}
    }
    else // TYPE = 0
    {
        ITS_USHORT tempLen = (len % 2)? (len - 1) : len;

	ITS_CHAR* temp = (ITS_CHAR*)origAddr_.c_str();
	ITS_OCTET val = 0;
	int i = 0;

	for ( ; i < tempLen; )
	{
	    val = ((SetTBCDCharacter(temp[i])) & 0x0f) | 
                (((SetTBCDCharacter(temp[i+1])) & 0x0f) << 4);
     
            buf [bufIndex] = (val & 0xff); bufIndex++;
            i += 2;
	}

	if (len % 2) 
	{
	    val = SetTBCDCharacter(temp[i]) & 0x0f;
	    val |= 0xf0;
	    buf [bufIndex] = (val & 0xff); bufIndex++;
        }
    }

    buf [bufIndex] = protId_; bufIndex++;

    buf [bufIndex] = dataCodeScheme_; bufIndex++;

    memcpy(&buf [bufIndex], srvCenterTS_, MAX_SRV_CENTER_TS);
    bufIndex += MAX_SRV_CENTER_TS;

    if (usrDataStrLen_ && usrDataStr_)
    {
        memcpy (&buf [bufIndex], usrDataStr_, usrDataStrLen_);
        bufIndex += usrDataStrLen_;
    }

    if (dataLen >= bufIndex)
    {
        memcpy (data, buf, bufIndex);
        dataLen = bufIndex;
        return ITS_SUCCESS;
    }
    else
    {
        return bufIndex;
    }
}

int
MapUserInfo_SMSDeliver::Decode (ITS_OCTET* data, ITS_USHORT dataLen)
{
    ITS_USHORT bufIndex = 0;
    Initialize();

    msgTypeInd_ = data[bufIndex] & 0x03;
    moreMsgsToSend_ = (data[bufIndex] & 0x04)? ITS_TRUE : ITS_FALSE;
    replyPath_ = (data[bufIndex] & 0x80)? ITS_TRUE : ITS_FALSE;
    usrDataHdrInd_ = (data[bufIndex] & 0x40)? ITS_TRUE : ITS_FALSE;
    statRepInd_ = (data[bufIndex] & 0x20)? ITS_TRUE : ITS_FALSE;

    bufIndex++;

    origAddrLen_ = data[bufIndex]; bufIndex++;
    origAddrType_ = data[bufIndex]; bufIndex++;

    origAddr_ = "";

    if(origAddrType_ == 0xD0)
    {
        char* bit7str = (char*)malloc(origAddrLen_);
        for (int i = 0; i < origAddrLen_; i++)
        {
            bit7str[i] = (char)SevenBitGet (&data[bufIndex], i);
        }

        char* asciistr = NULL;
        int len = convert_7bit_to_ascii(bit7str, 
                            origAddrLen_, &asciistr);
        if (asciistr)
        {
            origAddr_ = asciistr;
            free (asciistr);
        }

        free (bit7str);
    }
    else //Type = 0
    {
        ITS_USHORT templen = (origAddrLen_ % 2)? (origAddrLen_ - 1) : origAddrLen_;

	char valch = 0;
	for (int i = 0; i < templen; i+=2)
	{
		origAddr_ += GetTBCDCharacter (data[bufIndex] & 0x0f);
		origAddr_ += GetTBCDCharacter ((data[bufIndex] & 0xf0) >> 4);        
		bufIndex++;
	}

	if (origAddrLen_ % 2)
	{
		origAddr_ += GetTBCDCharacter (data[bufIndex] & 0x0f);
		bufIndex++;
	}
    }

    protId_ = data[bufIndex]; bufIndex++;
    dataCodeScheme_ = data[bufIndex]; bufIndex++;

    memcpy (srvCenterTS_, &data[bufIndex], MAX_SRV_CENTER_TS);
    bufIndex += MAX_SRV_CENTER_TS;

    if (dataLen > bufIndex)
    {
        usrDataStrLen_ = dataLen - bufIndex;
        memcpy (usrDataStr_, &data[bufIndex], usrDataStrLen_);
    }

    return ITS_SUCCESS;
}

void
MapUserInfo_SMSDeliver::Print()
{
    printf ("\nmsgTypeInd : %d\n",msgTypeInd_);

    if (moreMsgsToSend_)
        printf ("moreMsgsToSend : ITS_TRUE\n");
    else
        printf ("moreMsgsToSend : ITS_FALSE\n");

    if (replyPath_)
         printf ("replyPath : ITS_TRUE\n");
    else
         printf ("replyPath : ITS_FALSE\n");

    if (usrDataHdrInd_)
        printf ("usrDataHdrInd : ITS_TRUE\n");
    else
        printf ("usrDataHdrInd : ITS_FALSE\n");

    if (statRepInd_)
        printf ("statRepInd : ITS_TRUE\n");
    else
        printf ("statRepInd : ITS_FALSE\n");

    printf ("origAddrLen : %d\n",origAddrLen_);

    printf ("origAddrType : %d\n",origAddrType_);
    printf ("\tType of Number : %d\n",GET_TYPE_OF_NUMBER(origAddrType_));
    printf ("\tNumbering Plan : %d\n",GET_NUMBERING_PLAN(origAddrType_));

    printf ("origAddr : %s\n",origAddr_.c_str());

    printf ("protId : %d\n",protId_);

    printf ("dataCodeScheme : %d\n",dataCodeScheme_);
    printf ("\tCoding Group : %d\n",GET_CODING_GROUP(dataCodeScheme_));
    printf ("\tAlphabet Used : %d\n",GET_ALPHABET_USED(dataCodeScheme_));
    printf ("\tMessage Class : %d\n",GET_MSG_CLASS(dataCodeScheme_));

    printf ("Service Center TimeStamp : ");

    for (int i = 0; i < 7; i++)
        printf ("%02x ",srvCenterTS_[i]);
    printf("\n");

    ValidityPeriod vperiod;

    CalculateValidityPeriod(0x01, srvCenterTS_, &vperiod);
    printf ("TimeStamp : \n");
    printf ("Day         : %02x\n",vperiod.day & 0xff);
    printf ("month       : %02x\n",vperiod.month);
    printf ("year        : %02x\n",vperiod.year);
    printf ("hour        : %02x\n",vperiod.hour);
    printf ("minute      : %02x\n",vperiod.minute);
    printf ("second      : %02x\n",vperiod.second);
    printf ("timezone    : %02x\n",vperiod.timezone);
    printf ("TP-VP value : %d secs\n",vperiod.tpvpValue);

    ITS_OCTET str[255];
    ITS_UINT strLen = 255;
    GetUserData(str, &strLen);

    printf ("\nUser data : \n");
    for (int j = 0; j < strLen; j++)
        printf ("%02x ", str[j]);
    printf("\n");
}

MapUserInfo_SMSStatusReport::MapUserInfo_SMSStatusReport()
{
    Initialize ();
}

MapUserInfo_SMSStatusReport::MapUserInfo_SMSStatusReport (ITS_OCTET* usrInfo, 
                                                          ITS_USHORT usrInfoLen)
{
    Initialize ();
    Decode (usrInfo, usrInfoLen);
}

void MapUserInfo_SMSStatusReport :: Initialize ()
{
    msgTypeInd_     = 0;
    usrDtHdrInd_    = ITS_FALSE;
    moreMsgsToSend_ = ITS_FALSE;
    statRepQul_     = ITS_FALSE;
    msgRef_         = 0;
    recAddrLen_     = 0;
    recAddrType_    = 0;
    recAddr_        = "";
    memset (srvCenterTS_, MAX_VALIDITY_PERIOD_LEN, 0);
    memset (disTime_, MAX_VALIDITY_PERIOD_LEN, 0);
    status_         = 0;
    paramInd_       = 0;
    protId_         = 0;
    dataCodeScheme_ = 0;
    memset(usrDataStr_, MAX_USER_DATA_LEN, 0);
    usrDataStrLen_ = 0;

    paramIndPresent_   = ITS_FALSE;
    protIdPresent_     = ITS_FALSE;
    dataCodeSchemePresent_ = ITS_FALSE;
    usrDataPresent_ = ITS_FALSE;
}

void
MapUserInfo_SMSStatusReport::SetMessageIndicator (ITS_OCTET msgTypeInd)
{
    msgTypeInd_ = msgTypeInd;
}

ITS_OCTET
MapUserInfo_SMSStatusReport::GetMessageIndicator () const
{
    return msgTypeInd_;
}

void 
MapUserInfo_SMSStatusReport::SetUserDataHdrInd (ITS_BOOLEAN usrDtHdrInd)
{
    usrDtHdrInd_ = usrDtHdrInd;
}

ITS_BOOLEAN
MapUserInfo_SMSStatusReport::GetUserDataHdrInd () const
{
    return usrDtHdrInd_;
}

void
MapUserInfo_SMSStatusReport::SetMoreMsgsToSend (ITS_BOOLEAN moreMsgsToSend)
{
    moreMsgsToSend_ = moreMsgsToSend;
}

ITS_BOOLEAN
MapUserInfo_SMSStatusReport::GetMoreMsgsToSend () const
{
    return moreMsgsToSend_;
}

void
MapUserInfo_SMSStatusReport::SetStatusReportQualifier (ITS_BOOLEAN statRepQul)
{
    statRepQul_ = statRepQul;
}

ITS_BOOLEAN
MapUserInfo_SMSStatusReport::GetStatusReportQualifier () const
{
    return statRepQul_;
}

void
MapUserInfo_SMSStatusReport::SetMsgReference (ITS_OCTET msgRef)
{
    msgRef_ = msgRef;
}

ITS_OCTET
MapUserInfo_SMSStatusReport::GetMsgReference () const
{
    return msgRef_;
}

void
MapUserInfo_SMSStatusReport::SetRecipientAddr (ITS_OCTET recAddrLen,
                           ITS_OCTET recAddrType,
                           std::string recAddr)
{
    recAddrLen_ = recAddrLen;
    recAddrType_ = recAddrType;
    recAddr_ = recAddr;
}

void
MapUserInfo_SMSStatusReport::GetRecipientAddr (ITS_OCTET& recAddrLen,
             ITS_OCTET& recAddrType,
             std::string& recAddr)
{
    recAddrLen = recAddrLen_;
    recAddrType = recAddrType_;
    recAddr = recAddr_;
}

void
MapUserInfo_SMSStatusReport::SetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS)
{
    if (srvCenterTS == NULL) return;

    memcpy (srvCenterTS_, srvCenterTS, 7);
}

void
MapUserInfo_SMSStatusReport::GetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS) const
{
    if (srvCenterTS == NULL) return;

    memcpy (srvCenterTS, srvCenterTS_, 7);
}

void
MapUserInfo_SMSStatusReport::SetDischargeTime (ITS_OCTET* disTime)
{
    if (disTime == NULL) return;

    memcpy (disTime_, disTime, 7);
}

void
MapUserInfo_SMSStatusReport::GetDischargeTime (ITS_OCTET* disTime) const
{
    if (disTime == NULL) return;

    memcpy (disTime, disTime_, 7);
}

void
MapUserInfo_SMSStatusReport::SetStatus (ITS_OCTET status)
{
    status_ = status;
}

ITS_OCTET
MapUserInfo_SMSStatusReport::GetStatus () const
{
    return status_;
}

void
MapUserInfo_SMSStatusReport::SetParameterInd (ITS_OCTET paramInd)
{
    paramInd_ = paramInd;
    paramIndPresent_ = ITS_TRUE;
}

ITS_OCTET
MapUserInfo_SMSStatusReport::GetParameterInd () const
{
    return paramInd_;
}

void
MapUserInfo_SMSStatusReport::SetProtocolId (ITS_OCTET protId)
{
    protId_ = protId;
    protIdPresent_ = ITS_TRUE;
}

ITS_OCTET
MapUserInfo_SMSStatusReport::GetProtocolId () const
{
    return protId_;
}

void
MapUserInfo_SMSStatusReport::SetDataCodingScheme (ITS_OCTET dataCodeScheme)
{
    dataCodeScheme_ = dataCodeScheme;
    dataCodeSchemePresent_ = ITS_TRUE;
}

ITS_OCTET
MapUserInfo_SMSStatusReport::GetDataCodingScheme () const
{
    return dataCodeScheme_;
}

ITS_INT
MapUserInfo_SMSStatusReport::SetUserData (ITS_OCTET* usrData, ITS_UINT usrDataLen)
{
    if (usrDataLen && usrData)
    {
        memcpy (usrDataStr_, usrData, usrDataLen);
        usrDataStrLen_ = usrDataLen;
        return ITS_SUCCESS;
    }

    return ITS_ENULLPTR;
}

ITS_INT
MapUserInfo_SMSStatusReport::GetUserData (ITS_OCTET* usrData, ITS_UINT* usrDataLen)
{

    if (*usrDataLen >= usrDataStrLen_)
    {
        memcpy(usrData, usrDataStr_, usrDataStrLen_);
        *usrDataLen = usrDataStrLen_;
        return ITS_SUCCESS;
    }
    
    return usrDataStrLen_;
}

int
MapUserInfo_SMSStatusReport::Encode (ITS_OCTET* data, ITS_USHORT& dataLen)
{
    ITS_OCTET buf[255];
    ITS_USHORT bufIndex = 0;

    memset (buf, 0, 255);

    buf[bufIndex] = 0;
    buf[bufIndex] = (msgTypeInd_ & 0x03);

    if (moreMsgsToSend_)
    {
        buf[bufIndex] |= 0x04;
    }

    if (statRepQul_)
    {
        buf [bufIndex] |= 0x20;
    }

    if (usrDtHdrInd_)
    {
        buf [bufIndex] |= 0x40;
    }

    bufIndex++;
    buf [bufIndex] = msgRef_; bufIndex++;
    buf [bufIndex] = (recAddrLen_ & 0xff); bufIndex++;
    buf [bufIndex] = (recAddrType_ & 0xff); bufIndex++;

    int len = strlen (recAddr_.c_str());

    if (len > MAX_ORIG_ADDR_LEN)
    {
        return -1;
    }

    ITS_USHORT tempLen = (len % 2)? (len - 1) : len;

    ITS_CHAR* temp = (ITS_CHAR*)recAddr_.c_str();
    ITS_OCTET val = 0;
    int i = 0;

    for ( ; i < tempLen; )
    {
        val = ((SetTBCDCharacter(temp[i])) & 0x0f) | 
                  (((SetTBCDCharacter(temp[i+1])) & 0x0f) << 4);
     
        buf [bufIndex] = (val & 0xff); bufIndex++;
        i += 2;
    }

    if (len % 2) 
    {
        val = SetTBCDCharacter(temp[i]) & 0x0f;
        val |= 0xf0;
        buf [bufIndex] = (val & 0xff); bufIndex++;
    }

    memcpy(&buf [bufIndex], srvCenterTS_, MAX_SRV_CENTER_TS);
    bufIndex += MAX_SRV_CENTER_TS;

    memcpy(&buf [bufIndex], disTime_, MAX_SRV_CENTER_TS);
    bufIndex += MAX_SRV_CENTER_TS;

    buf [bufIndex] = status_; bufIndex++;

    if (paramIndPresent_)
    {
        buf [bufIndex] = paramInd_; bufIndex++;

        if (protIdPresent_)
        {
            buf [bufIndex] = protId_; bufIndex++;

            if (dataCodeSchemePresent_)
            {
                buf [bufIndex] = dataCodeScheme_; bufIndex++;
             
                if (usrDataStrLen_)
                {
                    memcpy (&buf [bufIndex], usrDataStr_, usrDataStrLen_);
                    bufIndex += usrDataStrLen_;
                }
            }
        } 
    }

    if (dataLen >= bufIndex)
    {
        memcpy (data, buf, bufIndex);
        dataLen = bufIndex;
        return ITS_SUCCESS;
    }
    else
    {
        return bufIndex;
    }
}

int
MapUserInfo_SMSStatusReport::Decode (ITS_OCTET* data, ITS_USHORT dataLen)
{
    ITS_USHORT bufIndex = 0;
    Initialize();

    msgTypeInd_ = data[bufIndex] & 0x03;
    moreMsgsToSend_ = (data[bufIndex] & 0x04)? ITS_TRUE : ITS_FALSE;
    statRepQul_ = (data[bufIndex] & 0x20)? ITS_TRUE : ITS_FALSE;
    usrDtHdrInd_ = (data[bufIndex] & 0x40)? ITS_TRUE : ITS_FALSE;

    bufIndex++;

    msgRef_ = data[bufIndex];

    bufIndex++;    
    recAddrLen_ = data[bufIndex]; bufIndex++;
    recAddrType_ = data[bufIndex]; bufIndex++;

    recAddr_ = "";

    ITS_USHORT templen = (recAddrLen_ % 2)? (recAddrLen_ - 1) : recAddrLen_;

    char valch = 0;
    for (int i = 0; i < templen; i+=2)
    {
        recAddr_ += GetTBCDCharacter (data[bufIndex] & 0x0f);
        recAddr_ += GetTBCDCharacter ((data[bufIndex] & 0xf0) >> 4);        
        bufIndex++;
    }
  
    if (recAddrLen_ % 2)
    {
        recAddr_ += GetTBCDCharacter (data[bufIndex] & 0x0f);
        bufIndex++;
    }

    memcpy (srvCenterTS_, &data[bufIndex], MAX_SRV_CENTER_TS);
    bufIndex += MAX_SRV_CENTER_TS;

    memcpy (disTime_, &data[bufIndex], MAX_SRV_CENTER_TS);
    bufIndex += MAX_SRV_CENTER_TS;

    status_ = data[bufIndex]; bufIndex++;

    if (dataLen > bufIndex)
    {
        paramInd_ = data[bufIndex]; bufIndex++;

        if (dataLen > bufIndex)
        {
            protId_ = data[bufIndex]; bufIndex++;

            if (dataLen > bufIndex)
            {
                dataCodeScheme_ = data[bufIndex]; bufIndex++;

                if (dataLen > bufIndex)
                {
                    usrDataStrLen_ = dataLen - bufIndex;
                    memcpy (usrDataStr_, &data[bufIndex], usrDataStrLen_);
                }
            }
        }
    }

    return ITS_SUCCESS;
}

void
MapUserInfo_SMSStatusReport::Print()
{
    printf ("\nmsgTypeInd : %d\n",msgTypeInd_);

    if (moreMsgsToSend_)
        printf ("moreMsgsToSend : ITS_TRUE\n");
    else
        printf ("moreMsgsToSend : ITS_FALSE\n");

    if (usrDtHdrInd_)
        printf ("usrDataHdrInd : ITS_TRUE\n");
    else
        printf ("usrDataHdrInd : ITS_FALSE\n");

    if (statRepQul_)
        printf ("statRepQal : ITS_TRUE\n");
    else
        printf ("statRepQal : ITS_FALSE\n");

    printf ("MsgRef : %d\n",msgRef_);
    printf ("recAddrLen : %d\n",recAddrLen_);

    printf ("recAddrType : %d\n",recAddrType_);
    printf ("\tType of Number : %d\n",GET_TYPE_OF_NUMBER(recAddrType_));
    printf ("\tNumbering Plan : %d\n",GET_NUMBERING_PLAN(recAddrType_));

    printf ("recAddr : %s\n",recAddr_.c_str());

    printf ("Service Center TimeStamp : ");

    int i;
    for (i = 0; i < 7; i++)
        printf ("%02x ",srvCenterTS_[i]);
    printf("\n");

    printf ("Discharge TimeStamp : ");

    for (i = 0; i < 7; i++)
        printf ("%02x ",disTime_[i]);
    printf("\n");

    printf ("paramInd : %d\n",paramInd_);

    printf ("protId : %d\n",protId_);

    printf ("dataCodeScheme : %d\n",dataCodeScheme_);
    printf ("\tCoding Group : %d\n",GET_CODING_GROUP(dataCodeScheme_));
    printf ("\tAlphabet Used : %d\n",GET_ALPHABET_USED(dataCodeScheme_));
    printf ("\tMessage Class : %d\n",GET_MSG_CLASS(dataCodeScheme_));

    ITS_OCTET str[255];
    ITS_UINT strLen = 255;
    GetUserData(str, &strLen);

    printf ("\nUser data : \n"); 
    for (int j = 0; j < strLen; j++)
        printf ("%02x ", str[j]);
    printf("\n");
}
