// Copy this to browser console



config = {
  keys: 'stations,labels',
  samples: [
    []
  ],
  test_groups: [
    [1],
    [2],
    [3],
    [4, 5],
    [5]
  ],
  points: [5, 8, 16, 10, 61]
}
var numberOfSubtasks = Math.max(10, config.test_groups.length);

function getSampleInputName(sample, subtask) {
  return 'sampleTestCaseSubtaskIds[' + sample + '][' + subtask + ']';
}

function getTestGroupInputName(test_group, subtask) {
  return 'testGroupSubtaskIds[' + test_group + '][' + subtask + ']';
}

function getSubtaskPointsInputName(subtask) {
  return 'subtaskPoints[' + subtask + ']';
}

function fillKeys() {
  $('input[name="sourceFileFieldKeys"]').val(config.keys);
}

function fillSampleCasesSubtasksAllocation() {
  for (var sample = 0; sample < config.samples.length; ++sample) {
    for (var subtask = 0; subtask < numberOfSubtasks; ++subtask) {
      $('input[name="' + getSampleInputName(sample, subtask) + '"]').prop("checked", false);
    }
    for (const subtask of config.samples[sample]) {
      $('input[name="' + getSampleInputName(sample, subtask - 1) + '"]').prop("checked", true);
    }
  }
}

function fillTestGroupsSubtasksAllocation() {
  for (var test_group = 0; test_group < config.test_groups.length; ++test_group) {
    if ($('input[name="' + getTestGroupInputName(test_group, 0) + '"]').length == 0) {
      $("#test-group-add").click();
    }
    for (var subtask = 0; subtask < numberOfSubtasks; ++subtask) {
      $('input[name="' + getTestGroupInputName(test_group, subtask) + '"]').prop("checked", false);
    }
    for (const subtask of config.test_groups[test_group]) {
      $('input[name="' + getTestGroupInputName(test_group, subtask - 1) + '"]').prop("checked", true);
    }
  }
}

function fillSubtasksPoints() {
  for (var subtask = 0; subtask < config.points.length; ++subtask) {
    $('input[name="' + getSubtaskPointsInputName(subtask) + '"]').val(
        config.points[subtask]);
  }
  for (var subtask = config.points.length; subtask < numberOfSubtasks; ++subtask) {
    $('input[name="' + getSubtaskPointsInputName(subtask) + '"]').val("");
  }
}

function fillCustomScorer() {
  $('select[name="customScorer"]').val("checker.cpp");
}

fillKeys();
fillSampleCasesSubtasksAllocation();
fillTestGroupsSubtasksAllocation();
fillSubtasksPoints();
fillCustomScorer();
