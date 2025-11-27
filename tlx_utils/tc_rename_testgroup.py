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


def get_input_subtasks(filename):
    tc = filename[:-len('.in')]
    if 's' in tc:
        return 'sample'

    subtasks = []
    if 'a' in tc:
        subtasks.append(1)
    if 'b' in tc:
        subtasks.append(2)
    if 'c' in tc:
        subtasks.append(3)
    if 'd' in tc:
        subtasks.append(4)
    if 'e' in tc:
        subtasks.append(5)
    if 'f' in tc:
        subtasks.append(6)
    if 'g' in tc:
        subtasks.append(7)
    if 'h' in tc:
        subtasks.append(8)
    if 'i' in tc:
        subtasks.append(9)

    return tuple(subtasks)


def get_input_sample_number(filename):
    return int(filename[:2])


def main():
    tcs = []
    tc_id_to_testgroups = {}
    testgroup_counter = collections.Counter()
    subtasks_to_testgroups = {}
    subtasks_to_testgroups['sample'] = 'sample'

    for filename in os.listdir(INPUT_DIR):
        if not is_input_tc(filename):
            continue

        tc_id = get_input_tc_id(filename)
        subtasks = get_input_subtasks(filename)
        if subtasks not in subtasks_to_testgroups:
            subtasks_to_testgroups[subtasks] = len(subtasks_to_testgroups)
        testgroup = subtasks_to_testgroups[subtasks]

        testgroup_counter[testgroup] += 1
        tc_num = get_input_sample_number(filename) if testgroup == 'sample' else testgroup_counter[testgroup]
        tc_id_to_testgroups[tc_id] = (testgroup, tc_num)

        ori_filename = os.path.join(INPUT_DIR, filename)
        new_filename = '{}_{}_{}.in'.format(SLUG, testgroup, tc_num)
        shutil.copy(ori_filename, new_filename)
        tcs.append(new_filename)

    for filename in os.listdir(OUTPUT_DIR):
        if not is_output_tc(filename):
            continue

        tc_id = get_output_tc_id(filename)
        testgroup, tc_num = tc_id_to_testgroups[tc_id]

        ori_filename = os.path.join(OUTPUT_DIR, filename)
        new_filename = '{}_{}_{}.out'.format(SLUG, testgroup, tc_num)
        shutil.copy(ori_filename, new_filename)
        tcs.append(new_filename)

    with zipfile.ZipFile(f'{SLUG}.zip', 'w') as zf:
        for tc in tcs:
            print('Adding: {}'.format(tc))
            zf.write(tc)
            os.remove(tc)

    print('Done renaming and zipping')

    testgroups_to_subtasks = {v: k for k, v in subtasks_to_testgroups.items() if k != 'sample'}
    for k in sorted(testgroups_to_subtasks):
        print(k, testgroups_to_subtasks[k])


if __name__ == '__main__':
    main()