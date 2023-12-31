/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import java.util.*;
import com.intellinet.diameter.mag.analysis.*;

public final class AGeneralAvpRef extends PGeneralAvpRef
{
    private PQualifier _qualifier_;
    private PAvpSpec _avpSpec_;

    public AGeneralAvpRef()
    {
    }

    public AGeneralAvpRef(
        PQualifier _qualifier_,
        PAvpSpec _avpSpec_)
    {
        setQualifier(_qualifier_);

        setAvpSpec(_avpSpec_);

    }
    public Object clone()
    {
        return new AGeneralAvpRef(
            (PQualifier) cloneNode(_qualifier_),
            (PAvpSpec) cloneNode(_avpSpec_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAGeneralAvpRef(this);
    }

    public PQualifier getQualifier()
    {
        return _qualifier_;
    }

    public void setQualifier(PQualifier node)
    {
        if(_qualifier_ != null)
        {
            _qualifier_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _qualifier_ = node;
    }

    public PAvpSpec getAvpSpec()
    {
        return _avpSpec_;
    }

    public void setAvpSpec(PAvpSpec node)
    {
        if(_avpSpec_ != null)
        {
            _avpSpec_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _avpSpec_ = node;
    }

    public String toString()
    {
        return ""
            + toString(_qualifier_)
            + toString(_avpSpec_);
    }

    void removeChild(Node child)
    {
        if(_qualifier_ == child)
        {
            _qualifier_ = null;
            return;
        }

        if(_avpSpec_ == child)
        {
            _avpSpec_ = null;
            return;
        }

    }

    void replaceChild(Node oldChild, Node newChild)
    {
        if(_qualifier_ == oldChild)
        {
            setQualifier((PQualifier) newChild);
            return;
        }

        if(_avpSpec_ == oldChild)
        {
            setAvpSpec((PAvpSpec) newChild);
            return;
        }

    }
}
