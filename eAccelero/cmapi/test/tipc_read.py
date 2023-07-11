#!/usr/bin/python

import sys
import os
# import xml.dom.minidom as md
import xml.sax as xs

DECODER = 'bin/debug/mdecode'
SYS_CMD_FMT = 'echo "%s" | ' + DECODER

def onValue(val):
    print '-' * 80
    print val
    os.system(SYS_CMD_FMT % val)
    print '-' * 80
    

"""
def parsePDML(dom):
    root = dom.getElementsByTagName('pdml')
    for packet in root[0].getElementsByTagName('packet'):
        for proto in packet.getElementsByTagName('proto'):
            if proto.getAttribute('name') == 'fake-field-wrapper':
                val = proto.getElementsByTagName('field')[0].getAttribute('value')
                onValue(val)

if __name__ == '__main__':
    dom = md.parse(sys.argv[1])
    parsePDML(dom)
"""

class SaxHandler(xs.ContentHandler):
    def __init__(self):
        xs.ContentHandler.__init__(self)

    def startElement(self, name, attrs):
        if name != 'field':
            return
        if attrs.getValue('name') != 'data':
            return
        #print '-' * 80
        #print attrs.getValue('value')
        onValue(attrs.getValue('value'))

    def endElement(self, name):
        pass
    

if __name__ == '__main__':
    xs.parse(sys.argv[1], SaxHandler())
    
