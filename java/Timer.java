import java.util.concurrent.TimeUnit;

public class Timer
{
    private long start;
    private long stop;

    private long delta_sec;
    private long delta_usec;

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
            return TimeUnit.SECONDS.convert(stop - start, TimeUnit.NANOSECONDS);
        return -1;
    }

    public long timer_get_usec_delta()
    {
        if(is_timer_setup())
            return stop - start;
        return -1;
    }

    public void update_delta() {
        this.delta_sec = this.timer_get_sec_delta();
        this.delta_usec = this.timer_get_usec_delta() % (long)1e6;
    }

    public void print(int v, int e, int stage) {
        this.update_delta();
        System.out.printf("%d,%d,%d,%d\n", v, e, stage, stop - start);

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
