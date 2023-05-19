import sys
import re

if len(sys.argv) < 3:
    print('Usage: python preprocess.py input_file output_file')
    sys.exit(1)
input_file = sys.argv[1]
output_file = sys.argv[2]
with open(input_file, 'r', encoding='utf-8') as f:
    text = f.read()
text = re.sub(r'[^а-яА-Я\s]', '', text).lower()
text = text.replace('\n', '')
text = re.sub(r'\s+', ' ', text)
text += " "
with open(output_file, 'w', encoding='utf-8') as f:
    f.write(text)
