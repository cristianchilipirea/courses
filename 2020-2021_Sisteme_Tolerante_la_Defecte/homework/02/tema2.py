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

	CMSOPTION = ['Wordpress', 'Joomla', 'Drupal']
	CMSREPLICAS = ['2', '3', '4', '5']
	SERVERWEBOPTION = ['Php+Apache']
	SERVERWEBREPLICAS = ['2', '3', '4', '5']
	DBOPTION = ['MongoDB', 'MySQL', 'MariaDB', 'Postgres', 'CouchDB', 'Redis']
	KEYWORDS = ['CMSOPTION', 'CMSREPLICAS', 'SERVERWEBOPTION', 'SERVERWEBREPLICAS', 'DBOPTION']

	in_csv_file = open(args.in_csv, newline='\n', encoding="utf8")
	tex_file_string = open(args.tex_file, 'r').read()

	csv_reader = csv.reader(in_csv_file, delimiter=',', quotechar='|')

	for row in csv_reader:
		out_row = row
		print(out_row)

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

if __name__ == "__main__":
	main()