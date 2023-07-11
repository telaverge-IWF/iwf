/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import java.util.*;
import com.intellinet.diameter.mag.analysis.*;

public final class AGroupedBody extends PGroupedBody
{
    private final LinkedList _fixed_ = new TypedLinkedList(new Fixed_Cast());
    private final LinkedList _required_ = new TypedLinkedList(new Required_Cast());
    private final LinkedList _optional_ = new TypedLinkedList(new Optional_Cast());

    public AGroupedBody()
    {
    }

    public AGroupedBody(
        List _fixed_,
        List _required_,
        List _optional_)
    {
        {
            this._fixed_.clear();
            this._fixed_.addAll(_fixed_);
        }

        {
            this._required_.clear();
            this._required_.addAll(_required_);
        }

        {
            this._optional_.clear();
            this._optional_.addAll(_optional_);
        }

    }
    public Object clone()
    {
        return new AGroupedBody(
            cloneList(_fixed_),
            cloneList(_required_),
            cloneList(_optional_));
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAGroupedBody(this);
    }

    public LinkedList getFixed()
    {
        return _fixed_;
    }

    public void setFixed(List list)
    {
        _fixed_.clear();
        _fixed_.addAll(list);
    }

    public LinkedList getRequired()
    {
        return _required_;
    }

    public void setRequired(List list)
    {
        _required_.clear();
        _required_.addAll(list);
    }

    public LinkedList getOptional()
    {
        return _optional_;
    }

    public void setOptional(List list)
    {
        _optional_.clear();
        _optional_.addAll(list);
    }

    public String toString()
    {
        return ""
            + toString(_fixed_)
            + toString(_required_)
            + toString(_optional_);
    }

    void removeChild(Node child)
    {
        if(_fixed_.remove(child))
        {
            return;
        }

        if(_required_.remove(child))
        {
            return;
        }

        if(_optional_.remove(child))
        {
            return;
        }

    }

    void replaceChild(Node oldChild, Node newChild)
    {
        for(ListIterator i = _fixed_.listIterator(); i.hasNext();)
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

        for(ListIterator i = _required_.listIterator(); i.hasNext();)
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

        for(ListIterator i = _optional_.listIterator(); i.hasNext();)
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

    private class Fixed_Cast implements Cast
    {
        public Object cast(Object o)
        {
            PNamedAvpRef node = (PNamedAvpRef) o;

            if((node.parent() != null) &&
                (node.parent() != AGroupedBody.this))
            {
                node.parent().removeChild(node);
            }

            if((node.parent() == null) ||
                (node.parent() != AGroupedBody.this))
            {
                node.parent(AGroupedBody.this);
            }

            return node;
        }
    }

    private class Required_Cast implements Cast
    {
        public Object cast(Object o)
        {
            PGeneralAvpRef node = (PGeneralAvpRef) o;

            if((node.parent() != null) &&
                (node.parent() != AGroupedBody.this))
            {
                node.parent().removeChild(node);
            }

            if((node.parent() == null) ||
                (node.parent() != AGroupedBody.this))
            {
                node.parent(AGroupedBody.this);
            }

            return node;
        }
    }

    private class Optional_Cast implements Cast
    {
        public Object cast(Object o)
        {
            PGeneralAvpRef node = (PGeneralAvpRef) o;

            if((node.parent() != null) &&
                (node.parent() != AGroupedBody.this))
            {
                node.parent().removeChild(node);
            }

            if((node.parent() == null) ||
                (node.parent() != AGroupedBody.this))
            {
                node.parent(AGroupedBody.this);
            }

            return node;
        }
    }
}
