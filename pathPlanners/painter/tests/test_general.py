def test_open_file_test():
	try:
		with open("non_existant_file") as foo:
			assert False
	except:
		assert True
