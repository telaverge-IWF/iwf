/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import java.util.*;
import com.intellinet.diameter.mag.analysis.*;

public final class AEnumDefinition extends PDefinition
{
    private TDocumentation _documentation_;
    private TIdentifier _name_;
    private TInteger _avpCode_;
    private final LinkedList _enumerator_ = new TypedLinkedList(new Enumerator_Cast());

    public AEnumDefinition()
    {
    }

    public AEnumDefinition(
        TDocumentation _documentation_,
        TIdentifier _name_,
        TInteger _avpCode_,
        List _enumerator_)
    {
        setDocumentation(_documentation_);

        setName(_name_);

        setAvpCode(_avpCode_);

        {
            this._enumerator_.clear();
            this._enumerator_.addAll(_enumerator_);
        }

    }
    public Object clone()
    {
        return new AEnumDefinition(
            (TDocumentation) cloneNode(_documentation_),
            (TIdentifier) cloneNode(_name_),
            (TInteger) cloneNode(_avpCode_),
            cloneList(_enumerator_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAEnumDefinition(this);
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

    public TInteger getAvpCode()
    {
        return _avpCode_;
    }

    public void setAvpCode(TInteger node)
    {
        if(_avpCode_ != null)
        {
            _avpCode_.parent(null);
        }

        if(node != null)
        {
            if(node.parent() != null)
            {
                node.parent().removeChild(node);
            }

            node.parent(this);
        }

        _avpCode_ = node;
    }

    public LinkedList getEnumerator()
    {
        return _enumerator_;
    }

    public void setEnumerator(List list)
    {
        _enumerator_.clear();
        _enumerator_.addAll(list);
    }

    public String toString()
    {
        return ""
            + toString(_documentation_)
            + toString(_name_)
            + toString(_avpCode_)
            + toString(_enumerator_);
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

        if(_avpCode_ == child)
        {
            _avpCode_ = null;
            return;
        }

        if(_enumerator_.remove(child))
        {
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

        if(_avpCode_ == oldChild)
        {
            setAvpCode((TInteger) newChild);
            return;
        }

        for(ListIterator i = _enumerator_.listIterator(); i.hasNext();)
        {
            if(i.next() == oldChild)
            {
                if(newChild != null)
                {
                    i.set(newChild);
                    oldChild.parent(null);
                    return;
                }

                i.remove();
                oldChild.parent(null);
                return;
            }
        }

    }

    private class Enumerator_Cast implements Cast
    {
        public Object cast(Object o)
        {
            PEnumerator node = (PEnumerator) o;

            if((node.parent() != null) &&
                (node.parent() != AEnumDefinition.this))
            {
                node.parent().removeChild(node);
            }

            if((node.parent() == null) ||
                (node.parent() != AEnumDefinition.this))
            {
                node.parent(AEnumDefinition.this);
            }

            return node;
        }
    }
}