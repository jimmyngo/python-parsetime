import unittest
import time
from parsetime import parsetime

class ParsetimeTest(unittest.TestCase):

    @classmethod
    def setUp(self):
        self.rtime = 1052136000

    def test_init(self):
        ptime = parsetime('')
        now = int(time.time())
        now = now - (now % 60)

        self.assertEquals(now, ptime)

    def test_date(self):
        ptime = parsetime('5:00 AM May 5 2003')
        self.assertEquals(self.rtime, ptime)

        ptime = parsetime('12:00 PM UTC May 5 2003')
        self.assertEquals(self.rtime, ptime)

    def test_add_sec(self):
        ptime = parsetime('5:00 AM May 5 2003+1s')
        self.assertEquals(self.rtime + 1, ptime)

        ptime = parsetime('5:00 AM May 5 2003+5sec')
        self.assertEquals(self.rtime + 5, ptime)

        ptime = parsetime('5:00 AM May 5 2003+10second')
        self.assertEquals(self.rtime + 10, ptime)

        ptime = parsetime('5:00 AM May 5 2003+15seconds')
        self.assertEquals(self.rtime + 15, ptime)

    def test_add_min(self):
        ptime = parsetime('5:00 AM May 5 2003+5min')
        self.assertEquals(self.rtime + 5 * 60, ptime)

        ptime = parsetime('5:00 AM May 5 2003+10minute')
        self.assertEquals(self.rtime + 10 * 60, ptime)

        ptime = parsetime('5:00 AM May 5 2003+15minutes')
        self.assertEquals(self.rtime + 15 * 60, ptime)

    def test_add_hour(self):
        ptime = parsetime('5:00 AM May 5 2003+1h')
        self.assertEquals(self.rtime + 1 * 3600, ptime)

        ptime = parsetime('5:00 AM May 5 2003+5hr')
        self.assertEquals(self.rtime + 5 * 3600, ptime)

        ptime = parsetime('5:00 AM May 5 2003+10hour')
        self.assertEquals(self.rtime + 10 * 3600, ptime)

        ptime = parsetime('5:00 AM May 5 2003+15hours')
        self.assertEquals(self.rtime + 15 * 3600, ptime)

    def test_add_day(self):
        ptime = parsetime('5:00 AM May 5 2003+1d')
        self.assertEquals(self.rtime + 1 * 3600 * 24, ptime)

        ptime = parsetime('5:00 AM May 5 2003+5day')
        self.assertEquals(self.rtime + 5 * 3600 * 24, ptime)

        ptime = parsetime('5:00 AM May 5 2003+10days')
        self.assertEquals(self.rtime + 10 * 3600 * 24, ptime)

    def test_add_week(self):
        ptime = parsetime('5:00 AM May 5 2003+1w')
        self.assertEquals(self.rtime + 1 * 3600 * 24 * 7, ptime)

        ptime = parsetime('5:00 AM May 5 2003+5wk')
        self.assertEquals(self.rtime + 5 * 3600 * 24 * 7, ptime)

        ptime = parsetime('5:00 AM May 5 2003+10week')
        self.assertEquals(self.rtime + 10 * 3600 * 24 * 7, ptime)

        ptime = parsetime('5:00 AM May 5 2003+15weeks')
        self.assertEquals(self.rtime + 15 * 3600 * 24 * 7, ptime)

    def test_add_month(self):
        ptime = parsetime('5:00 AM May 5 2003+5month')
        self.assertEquals(self.rtime + 3600 * 24 * 153, ptime)

        ptime = parsetime('5:00 AM May 5 2003+10month')
        self.assertEquals(self.rtime + 3600 * 24 * 305 + 3600, ptime)

    def test_add_year(self):
        ptime = parsetime('5:00 AM May 5 2003+1y')
        self.assertEquals(self.rtime + 3600 * 24 * 366, ptime)

        ptime = parsetime('5:00 AM May 5 2003+5year')
        self.assertEquals(self.rtime + 3600 * 24 * 5 * 365 + 2 * 24 * 3600, ptime)

        ptime = parsetime('5:00 AM May 5 2003+10years')
        self.assertEquals(self.rtime + 3600 * 24 * 10 * 365
                                     + 3 * 24 * 3600, ptime)

    def test_now(self):
        ptime = parsetime('now')
        now = int(time.time())

        self.assertEquals(now, ptime)

    def test_now_plus(self):
        ptime = parsetime('now+15min')
        now = int(time.time()) + (15 * 60)
        self.assertEquals(now, ptime)

    def test_now_minus(self):
        ptime = parsetime('now-15min')
        now = int(time.time()) - (15 * 60)

        self.assertEquals(now, ptime)

    def test_now_plusminus(self):
        ptime = parsetime('now-15min+10sec')
        now = int(time.time()) - (15 * 60) + 10

        ptime = parsetime('now-15hours-10seconds')
        now = int(time.time()) - (15 * 3600) - 10

        ptime = parsetime('now+15hours+10seconds')
        now = int(time.time()) + (15 * 3600) + 10

        self.assertEquals(now, ptime)


if __name__ == '__main__':
    unittest.main()
