/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import java.util.*;
import com.intellinet.diameter.mag.analysis.*;

public final class ANotEncryptable extends PEncryptable
{

    public ANotEncryptable()
    {
    }
    public Object clone()
    {
        return new ANotEncryptable();
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseANotEncryptable(this);
    }

    public String toString()
    {
        return "";
    }

    void removeChild(Node child)
    {
    }

    void replaceChild(Node oldChild, Node newChild)
    {
    }
}
