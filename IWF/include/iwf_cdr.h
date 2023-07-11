/**********************************-*-H-*-***********************************
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
 */


#ifndef __IWF_CDR_H__
#define __IWF_CDR_H__

#include <fstream>
#include <string>
#include <iomanip>
#include "iwf_fsm.h"

#include "Sync.h"

#define IWF_CDR_PATH            "/var/log/iwf/cdr/"
#define IWF_CAP_RO_CDR_PREFIX   "capro_cdr"

class IwfCDRWriter
{
 public:
    virtual ~IwfCDRWriter() {}
    virtual int Record(IwfFsm* ctxt, int failureCause = 0) = 0;
};

class IwfFormatter
{
 public:
    IwfFormatter(int indentLevel = 0)
        : m_indentLevel(indentLevel),
          m_fieldCount(0)
    {
    }
    virtual ~IwfFormatter() {}
    virtual IwfFormatter& StartRecord(std::ostream& os) = 0;
    virtual IwfFormatter& AddField(const std::string& name, const std::string& value) = 0;
    virtual IwfFormatter& AddField(const std::string& name, unsigned value) = 0;
    virtual IwfFormatter& AddField(const std::string& name, bool value) = 0;

    virtual IwfFormatter& AddField(const std::string& value) = 0;
    virtual IwfFormatter& AddField(unsigned value) = 0;
    virtual IwfFormatter& AddField(bool value) = 0;
    virtual IwfFormatter& AddFieldAsNull() = 0;
    virtual IwfFormatter& StopRecord() = 0;

 protected:
    int m_indentLevel;
    unsigned m_fieldCount;
};

class IwfCallDetailInterpreter
{
 public:
    virtual ~IwfCallDetailInterpreter() {}

    virtual int Record(IwfFormatter& formatter, IwfFsm* ctxt, int failureCause) = 0;
};

class IwfFileCDRWriter: public IwfCDRWriter
{
 public:

    IwfFileCDRWriter(const std::string& filePrefix,
                     IwfCallDetailInterpreter *interpreter);
    virtual ~IwfFileCDRWriter();

    virtual int Record(IwfFsm* ctxt, int failureCause = 0);

 protected:
    void CreateFile();

    std::string m_filePrefix;
    unsigned m_recordsCount;
    std::ofstream *m_outFile;
    eAccelero::Mutex m_fileGuard;
    std::string m_fileName;

    IwfFormatter *m_formatter;
    IwfCallDetailInterpreter *m_interpreter;
};

class IwfJsonFormatter: public IwfFormatter
{
 public:
    IwfJsonFormatter()
        : m_ostream(NULL)
    {
    }
    virtual IwfFormatter& StartRecord(std::ostream& os);
    virtual IwfFormatter& AddField(const std::string& name, const std::string& value);
    virtual IwfFormatter& AddField(const std::string& name, unsigned value);
    virtual IwfFormatter& AddField(const std::string& name, bool value);
    IwfFormatter& AddField(const std::string& value) {
        return *this;
    }
    IwfFormatter& AddField(unsigned value) {
        return *this;
    }
    IwfFormatter& AddField(bool value) {
        return *this;
    }
    IwfFormatter& AddFieldAsNull() {
        return *this;
    }
    virtual IwfFormatter& StopRecord();
 protected:
    void AddCommaIndent()
    {
        if (m_fieldCount)
        {
            (*m_ostream) << "," << std::endl;
        }
        (*m_ostream) << std::setfill(' ') << std::setw(m_indentLevel * 2) << "";
        m_fieldCount++;
    }
    std::ostream* m_ostream;
};

class IwfCsvFormatter: public IwfFormatter
{
 public:
    IwfCsvFormatter(const char fieldSep)
        : m_ostream(NULL),
        m_fieldSeparator(fieldSep)
    {
    }
    IwfFormatter& AddField(const std::string& name, const std::string& value) {
        return *this;
    }
    IwfFormatter& AddField(const std::string& name, unsigned value) {
        return *this;
    }
    IwfFormatter& AddField(const std::string& name, bool value) {
        return *this;
    }
    virtual IwfFormatter& StartRecord(std::ostream& os);
    virtual IwfFormatter& AddField(const std::string& value);
    virtual IwfFormatter& AddField(unsigned value);
    virtual IwfFormatter& AddField(bool value);
    virtual IwfFormatter& AddFieldAsNull();
    virtual IwfFormatter& StopRecord();
 protected:
    void AddFieldSeparator()
    {
        if (m_fieldCount)
        {
            (*m_ostream) << m_fieldSeparator;
        }
        m_fieldCount++;
    }
    std::ostream* m_ostream;
    const char m_fieldSeparator;
};

class IwfCallDetailRecorder
{
 public:
    IwfCallDetailRecorder(IwfCDRWriter* writer);
    ~IwfCallDetailRecorder();

    int Record(IwfFsm* ctxt, int failureCause)
    {
        return m_cdrWriter->Record(ctxt, failureCause);
    }

 protected:
    IwfCDRWriter* m_cdrWriter;
};

class IwfCapRoDetailInterpreter: public IwfCallDetailInterpreter
{
 public:
    virtual ~IwfCapRoDetailInterpreter() {}

    virtual int Record(IwfFormatter& formatter, IwfFsm* ctxt, int failureCause);
};

#endif // __IWF_CDR_H__
