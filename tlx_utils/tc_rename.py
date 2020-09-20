# Rename test cases with format names <subtask>-<tc_num>.[in|out] to toki format,
#   where subtask 0 will be renamed to sample
# Put this script in the same dir with the tests, then run `python3 tc_rename.py <slug>`

import os
import shutil
import sys
import zipfile


def rename_and_zip_test_cases(path, slug):
    tcs = []
    for filename in os.listdir():
        root, ext = os.path.splitext(filename)
        if ext not in ['.in', '.out']:
            continue
        
        subtask, tc_num = root.split('-')
        subtask, tc_num = int(subtask), int(tc_num)
        if subtask == 0:
            subtask = 'sample'
        
        new_filename = '{}_{}_{}{}'.format(slug, subtask, tc_num, ext)
        tcs.append(new_filename)

        shutil.copy(filename, new_filename)

    with zipfile.ZipFile('tc.zip', 'w') as zf:
        for tc in tcs:
            print('Adding: {}'.format(tc))
            zf.write(tc)
            os.remove(tc)

    print('Done renaming and zipping')


def main():
    slug, path = 'ioi-2020-tickets', '.'
    assert len(sys.argv) >= 2, 'Give slug'
    slug = sys.argv[1]
    if len(sys.argv) > 2:
        path = sys.argv[2]
    rename_and_zip_test_cases(path, slug)


if __name__ == '__main__':
    main()
