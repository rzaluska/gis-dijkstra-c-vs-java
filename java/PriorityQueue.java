class PriorityQueue
{
    private PQElem[] elements;
    private int first;
    private int next_free;
    private int size;

    public PriorityQueue(int max_elements)
    {
        elements = new PQElem[max_elements];
        first = -1;

        for (int i = 0; i < max_elements; ++i)
        {
            elements[i] = new PQElem();
        }
    }

    public void priority_queue_add_with_priority(int elem, int priority)
    {
        int element_index = next_free;
        PQElem new_elem = elements[element_index];
        next_free++;
        size++;
        new_elem.setVal(elem);
        new_elem.setIndex(element_index);
        new_elem.setPriority(priority);
        new_elem.setNext(-1);
        find_place_for_element(new_elem.getIndex());
    }

    void priority_queue_decrease_priority(int val, int new_priority)
    {
        PQElem curr = elements[first];
        PQElem prev = null;
        while (true)
        {
            if (curr.getVal() == val)
            {
                curr.setPriority(new_priority);
                if (curr.getIndex() != first)
                {
                    prev.setNext(curr.getNext());
                    find_place_for_element(curr.getIndex());
                }
                return;
            }
            if (curr.getNext() == -1)
            {
                break;
            }
            prev = curr;
            curr = elements[curr.getNext()];
        }
    }

    int priority_queue_extract_min()
    {
        PQElem min_elem = elements[first];
        int to_return = min_elem.getVal();
        size--;
        if (size > 0)
        {
            first = elements[min_elem.getNext()].getIndex();
        } else if (size == 0)
        {
            first = -1;
        }
        return to_return;
    }

    public boolean priority_queue_is_empty()
    {
        return size == 0;
    }

    public void priority_queue_free()
    {
        elements = null;
    }

    private void find_place_for_element(int new_index)
    {
        if (size == 1)
        {
            first = 0;
            return;
        }

        PQElem new_elem = elements[new_index];
        PQElem curr = elements[first];
        PQElem prev = null;

        while (true)
        {
            if (curr.getPriority() > new_elem.getPriority())
            {
                if (curr.getIndex() == first)
                {
                    first = new_elem.getIndex();
                } else
                {
                    prev.setNext(new_elem.getIndex());
                }
                new_elem.setNext(curr.getIndex());
                return;
            }
            prev = curr;
            if (curr.getNext() == -1)
            {
                break;
            }
            curr = elements[curr.getNext()];
        }
        //Add to end
        prev.setNext(new_elem.getIndex());
    }
}

class PQElem
{
    private int val;
    private int priority;
    private int next;
    private int index;

    public int getVal()
    {
        return val;
    }

    public void setVal(int val)
    {
        this.val = val;
    }

    public int getPriority()
    {
        return priority;
    }

    public void setPriority(int priority)
    {
        this.priority = priority;
    }

    public int getNext()
    {
        return next;
    }

    public void setNext(int next)
    {
        this.next = next;
    }

    public int getIndex()
    {
        return index;
    }

    public void setIndex(int index)
    {
        this.index = index;
    }
}