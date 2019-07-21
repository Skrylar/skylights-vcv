import unittest
import glob
import re

header_regex = re.compile("([a-z0-9]+-)*([a-z0-9]+).hh")
source_regex = re.compile("([a-z0-9]+-)*([a-z0-9]+).cc")

class TestFilenameConvention(unittest.TestCase):
    def test_headers(self):
        headers = glob.glob("*.hh")

        for f in headers:
            self.assertTrue(header_regex.match(f), f)

    def test_sources(self):
        sources = glob.glob("*.cc")

        for f in sources:
            self.assertTrue(source_regex.match(f), f)
