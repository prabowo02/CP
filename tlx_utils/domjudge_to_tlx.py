import collections
import os
import shutil
import zipfile


def rename(slug, problem_dir):
    tcs = []

    for tc_type in ['sample', 'secret']:
        tc_dir_location = os.path.join(problem_dir, 'data', tc_type)
        for filename in os.listdir(tc_dir_location):
            tc_id, ext = os.path.splitext(filename)
            if ext not in ('.in', '.ans'):
                continue

            tc_id = int(tc_id)
            subtask = 1 if tc_type == 'secret' else 'sample'

            ori_filename = os.path.join(tc_dir_location, filename)
            new_filename = '{}_{}_{}{}'.format(slug, subtask, tc_id, '.in' if ext == '.in' else '.out')
            shutil.copy(ori_filename, new_filename)
            tcs.append(new_filename)


    with zipfile.ZipFile('{}_tc.zip'.format(slug), 'w') as zf:
        for tc in tcs:
            print('Adding: {}'.format(tc))
            zf.write(tc)
            os.remove(tc)

    print('Done renaming and zipping')


if __name__ == '__main__':
    rename('gemastik-2025-penyisihan-a1', 'A1')
    rename('gemastik-2025-penyisihan-a2', 'A2')
    rename('gemastik-2025-penyisihan-b1', 'B1')
    # rename('gemastik-2025-penyisihan-b2', 'B2')
    rename('gemastik-2025-penyisihan-c', 'C')
    rename('gemastik-2025-penyisihan-d', 'D')
    rename('gemastik-2025-penyisihan-e', 'E')
    rename('gemastik-2025-penyisihan-f', 'F')
    rename('gemastik-2025-penyisihan-g1', 'G1')
    rename('gemastik-2025-penyisihan-g2', 'G2')
