import collections
import os
import shutil
import zipfile


SLUG = 'problem-slug'
INPUT_DIR = 'tests'
OUTPUT_DIR = 'tests'


def is_input_tc(filename):
    return filename.endswith('.in')


def is_output_tc(filename):
    return filename.endswith('.out')


def get_input_tc_id(filename):
    return filename[:-len('.in')]


def get_output_tc_id(filename):
    return filename[:-len('.out')]


def get_input_subtask(filename):
    if 'sample' in filename:
        return 'sample'

    with open(os.path.join(INPUT_DIR, filename)) as fp:
        def read_line_integers():
            return [int(s) for s in fp.readline().strip().split()]

        N, M = read_line_integers()

    if N == 1:
        return 1
    if N * M <= 100:
        return 2

    return 3


def get_input_sample_number(filename):
    return filename[len('sample'):-len('.in')]


def main():
    tcs = []
    tc_id_to_subtasks = {}
    subtask_counter = collections.Counter()

    for filename in os.listdir(INPUT_DIR):
        if not is_input_tc(filename):
            continue

        tc_id = get_input_tc_id(filename)
        subtask = get_input_subtask(filename)

        subtask_counter[subtask] += 1
        tc_num = get_input_sample_number(filename) if subtask == 'sample' else subtask_counter[subtask]
        tc_id_to_subtasks[tc_id] = (subtask, tc_num)

        ori_filename = os.path.join(INPUT_DIR, filename)
        new_filename = '{}_{}_{}.in'.format(SLUG, subtask, tc_num)
        shutil.copy(ori_filename, new_filename)
        tcs.append(new_filename)

    for filename in os.listdir(OUTPUT_DIR):
        if not is_output_tc(filename):
            continue

        tc_id = get_output_tc_id(filename)
        subtask, tc_num = tc_id_to_subtasks[tc_id]

        ori_filename = os.path.join(OUTPUT_DIR, filename)
        new_filename = '{}_{}_{}.out'.format(SLUG, subtask, tc_num)
        shutil.copy(ori_filename, new_filename)
        tcs.append(new_filename)

    with zipfile.ZipFile('tc.zip', 'w') as zf:
        for tc in tcs:
            print('Adding: {}'.format(tc))
            zf.write(tc)
            os.remove(tc)

    print('Done renaming and zipping')


if __name__ == '__main__':
    main()
