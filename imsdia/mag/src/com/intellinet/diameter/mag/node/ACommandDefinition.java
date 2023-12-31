/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import java.util.*;
import com.intellinet.diameter.mag.analysis.*;

public final class ACommandDefinition extends PDefinition
{
    private TDocumentation _documentation_;
    private TIdentifier _name_;
    private TIdentifier _identifier_;
    private PCommandHeader _commandHeader_;
    private PCommandBody _commandBody_;

    public ACommandDefinition()
    {
    }

    public ACommandDefinition(
        TDocumentation _documentation_,
        TIdentifier _name_,
        TIdentifier _identifier_,
        PCommandHeader _commandHeader_,
        PCommandBody _commandBody_)
    {
        setDocumentation(_documentation_);

        setName(_name_);

        setIdentifier(_identifier_);

        setCommandHeader(_commandHeader_);

        setCommandBody(_commandBody_);

    }
    public Object clone()
    {
        return new ACommandDefinition(
            (TDocumentation) cloneNode(_documentation_),
            (TIdentifier) cloneNode(_name_),
            (TIdentifier) cloneNode(_identifier_),
            (PCommandHeader) cloneNode(_commandHeader_),
            (PCommandBody) cloneNode(_commandBody_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseACommandDefinition(this);
    }

    public TDocumentation getDocumentation()
    {
        return _documentation_;
    }

    public void setDocumentation(TDocumentation node)
    {
        if(_documentation_ != null)
        {
            _documentation_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _documentation_ = node;
    }

    public TIdentifier getName()
    {
        return _name_;
    }

    public void setName(TIdentifier node)
    {
        if(_name_ != null)
        {
            _name_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _name_ = node;
    }

    public TIdentifier getIdentifier()
    {
        return _identifier_;
    }

    public void setIdentifier(TIdentifier node)
    {
        if(_identifier_ != null)
        {
            _identifier_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _identifier_ = node;
    }

    public PCommandHeader getCommandHeader()
    {
        return _commandHeader_;
    }

    public void setCommandHeader(PCommandHeader node)
    {
        if(_commandHeader_ != null)
        {
            _commandHeader_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _commandHeader_ = node;
    }

    public PCommandBody getCommandBody()
    {
        return _commandBody_;
    }

    public void setCommandBody(PCommandBody node)
    {
        if(_commandBody_ != null)
        {
            _commandBody_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _commandBody_ = node;
    }

    public String toString()
    {
        return ""
            + toString(_documentation_)
            + toString(_name_)
            + toString(_identifier_)
            + toString(_commandHeader_)
            + toString(_commandBody_);
    }

    void removeChild(Node child)
    {
        if(_documentation_ == child)
        {
            _documentation_ = null;
            return;
        }

        if(_name_ == child)
        {
            _name_ = null;
            return;
        }

        if(_identifier_ == child)
        {
            _identifier_ = null;
            return;
        }

        if(_commandHeader_ == child)
        {
            _commandHeader_ = null;
            return;
        }

        if(_commandBody_ == child)
        {
            _commandBody_ = null;
            return;
        }

    }

    void replaceChild(Node oldChild, Node newChild)
    {
        if(_documentation_ == oldChild)
        {
            setDocumentation((TDocumentation) newChild);
            return;
        }

        if(_name_ == oldChild)
        {
            setName((TIdentifier) newChild);
            return;
        }

        if(_identifier_ == oldChild)
        {
            setIdentifier((TIdentifier) newChild);
            return;
        }

        if(_commandHeader_ == oldChild)
        {
            setCommandHeader((PCommandHeader) newChild);
            return;
        }

        if(_commandBody_ == oldChild)
        {
            setCommandBody((PCommandBody) newChild);
            return;
        }

    }
}
