import java.util.concurrent.TimeUnit;

public class Timer
{
    private long start;
    private long stop;

    public void timer_start()
    {
        start = System.nanoTime();
    }
    public void timer_stop()
    {
        stop = System.nanoTime();
    }

    public long timer_get_sec_delta()
    {
        if(is_timer_setup())
            return TimeUnit.NANOSECONDS.convert(stop - start, TimeUnit.SECONDS);
        return -1;
    }

    public long timer_get_usec_delta()
    {
        if(is_timer_setup())
            return TimeUnit.NANOSECONDS.convert(stop - start, TimeUnit.MILLISECONDS);
        return -1;
    }

    private boolean is_timer_setup()
    {
        if(start == 0 || stop == 0)
        {
            System.out.println("Timer wasn't properly set up. Returning -1");
            return false;
        }
        return true;
    }
}
