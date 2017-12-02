class PriorityQueue
{
    private PQElem[] elements;
    private int [] lookup_index;
    private boolean [] present;
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

        lookup_index = new int[max_elements];
        present = new boolean[max_elements];
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
        lookup_index[elem] = element_index;
        present[element_index] = true;
    }

    void priority_queue_decrease_priority(int val, int new_priority)
    {
        int element_index = lookup_index[val];
        PQElem curr = elements[element_index];
        curr.setPriority(new_priority);
    }

    int priority_queue_extract_min()
    {
        int min = Integer.MAX_VALUE;
        int val = -1;
        int index = -1;

        for(int i = 0; i < next_free; ++i)
        {
            if(!present[i])
                continue;

            if(elements[i].getPriority() < min)
            {
                min = elements[i].getPriority();
                val = elements[i].getVal();
                index = i;
            }
        }

        present[index] = false;
        size--;
        return val;
    }

    public boolean priority_queue_is_empty()
    {
        return size == 0;
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