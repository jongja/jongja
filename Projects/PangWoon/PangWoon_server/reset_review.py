import store_dict as sd

for i in sd.store_dict:
    if sd.store_dict[i] == '':
        continue
    f = open('./review_data/' + sd.store_dict[i], 'w')
    f.write('0.0/0\n\n')
    f.close()


print('reset complete.')
