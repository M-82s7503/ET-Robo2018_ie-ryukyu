

def digital_img_map(d_arr):
    return [d_arr[6], d_arr[1], d_arr[0], d_arr[5], d_arr[2], d_arr[3], d_arr[4]]

def print_d_arr(d_maped_arr):
    for i in range(7):
        if i%3==0:
            if d_maped_arr[i] == 1:
                print(' - ', end='')
        else:
            if d_maped_arr[i] == 1:
                print('| ', end='')
            else:
                print('  ', end='')
        
        if i%3 != 1:
            print()
    print()
    print()
        

    

digital_arr = [[1,1,1,1,1,0,1], [1,0,0,1,0,0,0], [1,0,1,0,1,1,1], [1,0,0,1,1,1,1], [1,1,0,1,0,1,0], [0,1,0,1,1,1,1], [0,1,1,1,1,1,1], [1,0,0,1,0,0,1], [1,1,1,1,1,1,1]]

for i in range(9):
    tmp_arr = digital_img_map( digital_arr[i] )
    print_d_arr(tmp_arr)