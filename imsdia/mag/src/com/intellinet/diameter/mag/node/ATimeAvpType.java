/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import java.util.*;
import com.intellinet.diameter.mag.analysis.*;

public final class ATimeAvpType extends PAvpType
{

    public ATimeAvpType()
    {
    }
    public Object clone()
    {
        return new ATimeAvpType();
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseATimeAvpType(this);
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
