import hashlib
import argparse
import pandas as pd
import os
import csv
import subprocess
from random import choice

def main():
	parser = argparse.ArgumentParser(description='Generate the PDF homework ')
	parser.add_argument('--in_csv', help='csv file containing the STUDENT_NAME, STUDENT_USERNAME')
	parser.add_argument('--out_csv', help='csv file in which to output the resulting combinations')
	parser.add_argument('--tex_file', help='tex file in which to look for the bolded keywords')

	args = parser.parse_args()

	#print(f'in_csv is: {args.in_csv}')
	#print(f'out_csv is: {args.out_csv}')
	#print(f'tex_file is: {args.tex_file}')

	current_path = os.getcwd()
	homeworks_dir = os.path.join(current_path, 'homeworks')
	print(homeworks_dir)

	hash_dict = []

	IAOPTION = ['speech-to-text', 'translate', 'speech translation',\
		'face detection', 'form recognizer', 'OCR', 'image tagging',\
		'image description', 'sentiment analysis', 'entity extraction', \
		'anomaly detection', 'brand detection']
	KEYWORDS = ['IAOPTION']

	in_csv_file = open(args.in_csv, newline='\n', encoding="utf8")
	out_csv_file = open(args.out_csv, 'w+', newline='')
	tex_file_string = open(args.tex_file, 'r').read()

	csv_reader = csv.reader(in_csv_file, delimiter=',', quotechar='|')
	csv_writer = csv.writer(out_csv_file)

	for row in csv_reader:
		combination = [choice(IAOPTION)]
		out_row = row + combination
		print(out_row)

		csv_writer.writerow(out_row)

		current_string = tex_file_string.replace('NUMESTUDENT', row[0])

		for idx, word in enumerate(KEYWORDS):
			current_string = current_string.replace(word, out_row[2 + idx])

		homework_filename = row[1].replace('.', '_') + '.tex'
		homework_filename_path = os.path.join(homeworks_dir, homework_filename)
		homework_out_file = open(homework_filename_path, 'w+')
		homework_out_file.write(current_string)
		homework_out_file.close()
		os.chdir(homeworks_dir)
		subprocess.call(["pdflatex", homework_filename])
		os.chdir(current_path)

	in_csv_file.close()
	out_csv_file.close()

if __name__ == "__main__":
	main()