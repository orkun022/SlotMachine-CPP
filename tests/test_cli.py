import subprocess
import unittest
from pathlib import Path

BINARY = Path(__file__).resolve().parents[1] / 'slot-machine'

class CLITests(unittest.TestCase):
    def run_game(self, text='', *args):
        return subprocess.run([str(BINARY), *args], input=text, text=True, capture_output=True, timeout=3)

    def test_eof_exits(self):
        result = self.run_game()
        self.assertEqual(result.returncode, 0)
        self.assertIn('Spins: 0 | Balance: 100', result.stdout)

    def test_bad_input_does_not_spend_credits(self):
        result = self.run_game('invalid\n-1\n0\n11\n1.5\nq\n', '--seed', '42')
        self.assertIn('Spins: 0 | Balance: 100', result.stdout)
        self.assertEqual(result.stdout.count('Enter a whole-number'), 5)

    def test_fixed_seed_reproduces_session(self):
        first = self.run_game('1\n2\n3\nq\n', '--seed', '42')
        second = self.run_game('1\n2\n3\nq\n', '--seed', '42')
        self.assertEqual(first.stdout, second.stdout)
        self.assertIn('Spins: 3', first.stdout)

    def test_invalid_seed_is_rejected(self):
        self.assertEqual(self.run_game('', '--seed', '42bad').returncode, 2)

if __name__ == '__main__':
    unittest.main()
