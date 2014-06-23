import os

_file_name = 'file1.c'

LHS_dict = {}
RHS_dict = {}

def counting_variables:
	test_file = open(_file_name,'r+')
	
	for line in test_file:
		if 'int' in line or 'char' in line or 'double' in line or 'float' in line:
			count += line.count(',') + 1
	
	test_file.close()
	return count

def checking_constructs:
	test_file = open(_file_name,'r+')
	line_count = 1

	for line in test_file:
		line_count += 1
		
		if 'for' in line:
			print "for loop at line number %d\n", % (line_count)
			#TODO
		
		if 'while' in line:
			"while loop at line number %d\n", % (line_count)
			#TODO

		if 'if' in line :
			"if/else block at line number %d\n", % (line_count)
			#TODO
		
		else if ';' in line and '=' in line:
			"assignment at line number %d\n", % (line_count)
			storing_assigns(line,line_count)
			
			#TODO
	
	test_file.close()

def storing_assigns(line,line_count):
		
	line_list = line.split('=')

	LHS_dict[line_count] = line_list[0]
	RHS_dict[line_count] = line_list[1]
	
#def checking_dependency():

	
			

