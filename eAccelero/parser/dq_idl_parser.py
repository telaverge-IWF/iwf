#!/usr/bin/python

#Import parser module 
import dq_abnf_parser as sp
#Import regular expression module to support search and other function
import re
#Import sys module to support accessing command line arguments
import sys

# TODO code cleanup!

#parse_str = holds input data for parsing,
global parse_str
parse_str=''
global plain
plain = ''
#To hold porotcol buffer related data
global PBData
PBData = ''

class_val_start = 1000
meth_val_start = 1
meth_name = []
meth_val = []
meth_arg = []
parse_temp =[]
#Just holds each methods encoding format (PB ot NonPB)
encode_format = []

#template for headers
header_template ="""
#ifndef _INTERFACE_%s
#define _INTERFACE_%s

"""
#template for xx_def.h
template_str_def_h_meth = """
#define M_%s_%s %s
"""
template_str_def_h_class ="""
#define I_%s %s
"""
#template for xx.h
template_str_interface_h ="""
#include "%s"
#include "MeSSComponent.h"

"""

template_str_inerface_h_class = """
class %s:public eAccelero::Interface
{
public:
    %s():Interface(I_%s)
    { 
        eAccelero::MeSSComponent::Instance().MeSSObj().RegisterInterface(this);
    }
"""
template_str_inerface_h_meth = """
    virtual int %s(%s) = 0;
"""
template_str_inerface_h_des = """
    void RegisterMethods();
    virtual ~%s() { }
};

"""

#template for xxx.cpp
template_str_interface_cpp = """
#include "%s"

"""
template_str_interface_cpp_class = """
void %s::RegisterMethods()
{
"""
template_str_interface_cpp_meth = """
    this->RegisterMethod(M_%s_%s,eAccelero::MethodSlot<%s,
    %s,eAccelero::%s,eAccelero::%s>(this,&%s::%s));
"""
#template for namespace which should be called once
template_namespace_str = """
#include "MeSSComponent.h"
#include "%s"
#include "Interface.h"

using namespace eAccelero;

namespace Stub{
class %sRespCbk
{
public:
    %sRespCbk() { }
"""
#Protocol buffer related header files 
template_header_PB = """
#include "%s"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

"""
#template for callback methods which is pure virtual called for each methods in an interface
template_int_meth_cbk_str = """
    virtual int %sRespCbk(%s) = 0;
"""
 
template_int_meth_cbk_end_str = """
    void Register%sRespHandler();
    virtual ~%sRespCbk() { }
};
""" 

template_reg_resp_hdlr = """
#include "%s_caller.h"

using namespace Stub;

void %sRespCbk::Register%sRespHandler()
{
    %s
}
"""
template_reg_resp_hdlr_fn = """
    MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_%s, M_%s_%s),
        CallbackSlot<%sRespCbk, %s, %s, %s>(this, &%sRespCbk::%sRespCbk));
"""

template_int_str = """
class %s
{
public: 
    %s(MeSSEndpoint loc_dest,unsigned loc_flags = 0):
    m_dest(loc_dest),
    flags(loc_flags)
    {
    }
"""

template_int_meth_str = """
    int %s(%s,void *cookie = NULL)
    {
        MessageId msgid = MakeMsgId(I_%s,M_%s_%s);
        MeSSComponent::Instance().MeSSObj().Send(m_dest, msgid, (void*)&%s, sizeof(%s), (void *)cookie,flags);
        return 0;
    }
"""

template_int_cbk_template_str = """
    template <typename C>
    static void Set%sRespHandler(C *obj, int (C::*cbkFn)(%s*))
    {
        MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_%s, M_%s_%s),
        CallbackSlot<C, %s, %s, %s>(obj, cbkFn));
    }
"""

template_int_end_str = """
private:
    MeSSEndpoint m_dest;
    unsigned flags;
};
}//namespace Stub
"""

#Protocol buffer Encoding functions 
template_PB = """
    int %s(%s,void *cookie = NULL)
    {
        MessageId msgid = MakeMsgId(I_%s,M_%s_%s);
        MeSSComponent::Instance().MeSSObj().Send(m_dest, msgid, %s, cookie);
        return 0;
    }
"""

#definition for rendering xxx_def.h template
def create_interface_def(filename_PB,class_name,class_val,class_meth,meth_val,encode_format):
    global f_def
    global pb_done
    class_meth_upper = [x.upper() for x in class_meth]
    #checks if any method uses PB, if so related header files are added
    if not pb_done:
        for PB_name in encode_format:
            if PB_name == "uses_PB":
                f_def.write(template_header_PB % (filename_PB.replace(".proto",".pb.h")))
                pb_done = True;
                break;
    f_def.write(template_str_def_h_class % (class_name.upper(),class_val))
    for item2,item3 in zip(class_meth_upper,meth_val):
        f_def.write(template_str_def_h_meth % (class_name.upper(),item2,item3))

#definition for rendering xxx.h template
def create_interface(file_name,class_name,meth_name,meth_arg):
    global start
    global f
    tmp = []
    for args in meth_arg:
        tmp.append( '{0} *{1},{2} *{3}'.format(args[0],args[1],args[2],args[3]))
    if (start == 1):
        f.write(template_str_interface_h % (file_name))

    f.write(template_str_inerface_h_class % (class_name,class_name,class_name.upper()))
    for item2,item3  in zip(meth_name,tmp):
        f.write(template_str_inerface_h_meth % (item2,item3))
        
    f.write(template_str_inerface_h_des % (class_name))
        
#definition for rendering xxx.cpp template
def create_interface_cpp(filename,class_name,meth_name,meth_arg,encode_format):
    global start
    global f_cpp
    tmp = []
    meth_name_upper = [x.upper() for x in meth_name]
    for args in meth_arg:
        tmp.append( '{0},{1}'.format(args[0],args[2]))
    if (start==1):
        f_cpp.write(template_str_interface_cpp % (filename))
    f_cpp.write(template_str_interface_cpp_class % (class_name))
    #Each method differentiate register methods based on PB and NonPB  
    for item1,item2,item3,DataPB in zip(meth_name,tmp,meth_name_upper,encode_format):
        if DataPB == "uses_PB":
            f_cpp.write(template_str_interface_cpp_meth %(class_name.upper(),item3,class_name,item2,
            "PBEncodingTraits","PBEncodingPolicy",class_name,item1))
        else:
            f_cpp.write(template_str_interface_cpp_meth %(class_name.upper(),item3,class_name,item2,
            "FlatEncodingTraits","FlatEncodingPolicy",class_name,item1))
    f_cpp.write("}" + "\n")
    start = 0

#definition for rendering xxx.h template
def create_interface_caller(file_name,class_name,meth_name,meth_arg,encode_format):
    global start
    global f_caller
    global f_caller_cpp
    tmp1 = []
    tmp = []
    meth_name_upper = [x.upper() for x in meth_name]
    for args in meth_arg:
        tmp1.append( '{0} *{1}'.format(args[2],args[3]))
    f_caller.write(template_namespace_str % (file_name,class_name,class_name))

    for item2,item3  in zip(meth_name,tmp1):
        f_caller.write(template_int_meth_cbk_str % (item2,item3))
        
    f_caller.write(template_int_meth_cbk_end_str % (class_name,class_name))

    for args in meth_arg:
        tmp.append( '{0}& {1}'.format(args[0],args[1]))
    f_caller.write(template_int_str % (class_name,class_name))
    #Each method to differentiate encoding format and sending options based on PB and NonPB 
    for item2,item3,item4,DataPB in zip(meth_name,tmp,meth_name_upper,encode_format):
        item3_tmp = item3.split()
        if DataPB == "uses_PB":
            f_caller.write(template_PB % (item2,item3,class_name.upper(),\
            class_name.upper(),item4,item3_tmp[1]))
        else:
            f_caller.write(template_int_meth_str % (item2,item3,class_name.upper(),\
            class_name.upper(),item4,item3_tmp[1],item3_tmp[1]))

    regCbkStr = ''
    #Each method to differetiate registering callback slot for response callback
    for item1,item2,item3,DataPB in zip(meth_name,tmp1,meth_name_upper,encode_format):
        item2 = item2.split()
        if DataPB == "uses_PB":
            f_caller.write(template_int_cbk_template_str % (item1,item2[0],class_name.upper(),class_name.upper(),
            item3,item2[0],"PBEncodingTraits","PBEncodingPolicy"))
            regCbkStr += template_reg_resp_hdlr_fn % (class_name.upper(),\
                            class_name.upper(), item3, class_name, item2[0],\
                            "PBEncodingTraits","PBEncodingPolicy", class_name, item1)
        else:
            f_caller.write(template_int_cbk_template_str % (item1,item2[0],class_name.upper(),class_name.upper(),
            item3,item2[0],"FlatEncodingTraits","FlatEncodingPolicy"))
            regCbkStr += template_reg_resp_hdlr_fn % (class_name.upper(),\
                            class_name.upper(), item3, class_name, item2[0],\
                            "FlatEncodingTraits","FlatEncodingPolicy", class_name, item1)
    
    f_caller_cpp.write(template_reg_resp_hdlr % (class_name, class_name, class_name, regCbkStr))
    f_caller.write(template_int_end_str)

def GetPlain(tokens):
    global plain
    plain += tokens
    return None
#definition for collecting all PB related data
def GetPBData(tokens):
    global PBData
    PBData += tokens
    return None
#Start of Generic types would be using during creating an python object
#Identifiers will parse all the words separated by a space, atleast one word should be detected
comment = sp.LineCommentCplusType('\/\/')
header = sp.Regex(r'[a-zA-Z0-9_][a-zA-Z0-9-_]*',suppress=True)
identifiers = sp.Regex(r'[a-zA-Z0-9_][a-zA-Z0-9-_]*')
#identifiers_withptr = sp.Regex(r'[a-zA-Z0-9_][a-zA-Z0-9-_]*')
data_type = sp.Regex(r'[a-z][a-z]*')
cury_brace_open = sp.suppress('{')
cury_brace_close = sp.suppress('}')
normal_brace_open = sp.suppress('(')
normal_brace_close = sp.suppress(')')
#End of Generic types 

name_fmt = header
name = name_fmt.copy()
name.setName('interface')

interface_class_name = identifiers
interface_name = interface_class_name.copy()
interface_name.setName('interface')
interface_class  = interface_name
        
method_phase = sp.Repeat(sp.Group((identifiers + normal_brace_open +\
                           sp.Optional(sp.Repeat(identifiers) + sp.suppress(',') +\
                                sp.Repeat(identifiers)) +\
                            normal_brace_close + sp.Optional(sp.Literal("uses_PB"))) +\
                         sp.Optional(sp.Repeat(comment)) + sp.suppress(';')) + sp.Optional(sp.Repeat(comment)),
                    name='methods')
                        
interface_def = sp.Group(name + interface_class +\
                        sp.Optional(sp.Repeat(comment)) + cury_brace_open +\
                        sp.Optional(sp.Repeat(comment)) + method_phase +\
                        sp.Optional(comment) + cury_brace_close)

pre_rule = sp.suppress('%{') + sp.Not('%}', parse_action=GetPlain, suppress=True) + sp.suppress('%}')
#rule for parsing Pb related data
pre_rule_PB = sp.suppress('%PB{') + sp.Not('%PB}', parse_action=GetPBData, suppress=True) + sp.suppress('%PB}')

idl_grammar = sp.Repeat(sp.oneOfRules([comment,pre_rule_PB,pre_rule,interface_def]))

import optparse
import os

if __name__ == '__main__':
    idl_grammar = idl_grammar + sp.string_end

    cmd_args = optparse.OptionParser()
    cmd_args.add_option('-s', '--src', dest='src', default='',
                        help='IDL files directory location')
    cmd_args.add_option('-d', '--dest', dest='dest', default='.',
                        help='Destination directory for all generated files')
    cmd_args.add_option('-x', '--cpp', dest='cpp', default='',
                        help='Destination directory for CPP header and src files')
    cmd_args.add_option('-c', '--stub', dest='stub', default='',
                        help='Destination directory for Client/Caller stub')
    cmd_args.add_option('-i', '--server', dest='server', default='',
                        help='Destination directory for server/implementor code')
    cmd_args.add_option('-a', '--common', dest='common', default='',
                        help='Destination directory for common headers')
    cmd_args.add_option('-p', '--proto', dest='proto', default='',
                        help='Destination directory for generated proto files')
    cmd_args.add_option('-b', '--sep', dest='sep', default=False, action='store_true',
                        help='Put cpp files in src and headers in include dir')

    (options, args) = cmd_args.parse_args()

    stub_src = options.dest; stub_h = options.dest
    server_src = options.dest; server_h = options.dest
    proto_dir = options.dest; common_dir = options.dest
    src_dir = ''
    if options.src != '':
        src_dir = options.src
        args = filter(lambda x: x[-3:] == 'idl', os.listdir(src_dir))

    if options.cpp != '':
        stub_src = options.cpp; stub_h = options.cpp
        server_src = options.cpp; server_h = options.cpp
        common_dir = options.cpp

    if options.stub != '':
        stub_src = options.stub; stub_h = options.stub

    if options.server != '':
        server_src = options.server; server_h = options.server

    if options.common != '':
        common_dir = options.common

    if options.proto != '':
        proto_dir = options.proto

    if options.sep: stub_src += '/src'; stub_h += '/include'
    if options.sep: server_src += '/src'; server_h += '/include'
    if options.sep: common_dir += '/include'

    print 'Stub Src   dir: ', stub_src
    print 'Stub h     dir: ', stub_h
    print 'Server src dir: ', server_src
    print 'Server h   dir: ', server_h
    print 'Common h   dir: ', common_dir
    print 'Proto      dir: ', proto_dir
    print 'IDL files:', args

    # Create the directories
    for dir_name in [stub_src, stub_h, server_src, server_h, common_dir, proto_dir]:
        if not os.path.lexists(dir_name):
            os.mkdir(dir_name)
    
    if not os.path.lexists('interface_index'):
        class_val_start = 1000
    else:
        f_interface_idx = open('interface_index', 'r')
        class_val_start = int(f_interface_idx.read())
        f_interface_idx.close()
    print 'Interface index start: ', class_val_start

#    print '=' * 80
    #sys.argv.pop(0)
    global file1
    #Main loop to process all files sent by command lines
    for files in args:
        if src_dir != '': src_dir += '/'
        file1 = open(src_dir + files,"r")
        parse_str = file1.read()
        file1.close()
        idl_str = parse_str
        print 'Parsing %s' % (files)
        tokens = idl_grammar.parseString(idl_str)
#        print tokens
#        print '=' * 80
        #check if parse string has parsed output
        if(len(tokens)>=1):
            parse_tree = tokens[0]
            tokens = ''
        else:
            parse_tree = ''
        filename_def = common_dir + '/' + files.replace('.idl','_def.h')
        filename_def_i = files.replace('.idl','_def.h')
        filename_cpp = server_src + '/' + files.replace('.idl','.cpp')
        filename = server_h + '/' + files.replace('.idl','.h')
        filename_i = files.replace('.idl','.h')
        filename_PB = proto_dir + '/' + files.replace('.idl','.proto')
        filename_PB_i = files.replace('.idl','.proto')
        head_filename_def = files.replace('.idl','_def_h')
        head_filename_def = head_filename_def.upper()
        head_filename = files.replace('.idl','_h')
        head_filename  = head_filename.upper()
        for data in parse_tree:
            parse_temp.append(dict(data[0].items() + data[1].items()))
        global f_def
        f_def = open(filename_def,'w')
        f_def.write(header_template % (head_filename_def,head_filename_def))    
        global f
        f = open(filename,'w')
        f.write(header_template % (head_filename,head_filename))    
        global f_cpp
        f_cpp = open(filename_cpp,'w')
        global start
        start = 1
        pb_done = False
        global print_state
        print_state= 1
        for data_class in parse_temp:
            head_filename_caller = data_class['interface'] + '_caller_h'
            head_filename_caller  = head_filename_caller.upper()
            filename_caller = stub_h + '/' + data_class['interface'] + '_caller.h'
            filename_caller_cpp = stub_src + '/' + data_class['interface'] + '_caller.cpp'
            f_caller = open(filename_caller,'w')
            f_caller_cpp = open(filename_caller_cpp,'w')
            f_caller.write(header_template % (head_filename_caller,head_filename_caller))    
            for name in data_class['methods']:
                meth_name.append(name[0])
                meth_arg.append(reduce(lambda x,y: x+y,name[1]))
                #If array length is 3, it has PB keyword,just to differetiate 
                #PB and NOnPB methods
                if len(name) == 3:
                    encode_format.append(name[2])
                else:
                    encode_format.append("Not_PB")
                meth_val.append(meth_val_start)
                meth_val_start+=1
            if print_state ==1: print 'Generating %s' % (filename_def)
            create_interface_def(filename_PB_i,data_class['interface'],class_val_start,meth_name,meth_val,encode_format)
            if print_state ==1: print 'Generating %s' % (filename)
            create_interface(filename_def_i,data_class['interface'],meth_name,meth_arg)
            if print_state ==1: print 'Generating %s' % (filename_cpp)
            create_interface_cpp(filename_i,data_class['interface'],meth_name,meth_arg,encode_format)
            print 'Generating %s for %s' % (filename_caller,files) 
            print 'Generating %s for %s' % (filename_caller_cpp,files) 
            create_interface_caller(filename_def_i,data_class['interface'],meth_name,meth_arg,encode_format)
            print_state = 0
            class_val_start +=1
            meth_val_start = 1
            meth_name = []
            meth_val = []
            meth_arg = []
            encode_format = []
            f_caller.write('#endif' + '\n') 
            f_caller.close()
            f_caller_cpp.close()
        parse_temp = []
        f_def.write(plain.replace(".h","_def.h"))
        f_def.write('#endif' + '\n')
        f.write('#endif' + '\n') 
        f.close()
        f_def.close()
        plain = ''
        parse_tree = ''
        parse_str = ''
        #Check if any protocol buffer related data is declared
        #If so, Create a proto file else don't create it 
        if PBData == '':
            print "No Protocol buffer structure declaration"
        else:
            print "Creating Protocol buffer structure in a proto file"
            global f_PB
            f_PB = open(filename_PB,'w')
            f_PB.write(PBData)
            PBData = ''

    f_interface_index = open('interface_index', 'w')
    f_interface_index.write(str(class_val_start))
    f_interface_index.close()
