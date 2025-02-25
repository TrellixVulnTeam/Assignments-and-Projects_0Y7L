function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices.
%
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);

% You need to return the following variables correctly
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%

% add a column of ones to feed the bias node
labels = zeros(num_labels, 1);

for i = 1:num_labels
    labels(i) = i;
end

X = [ones(m, 1) X];

J_total = 0;   % labels
accummulator2 = zeros(num_labels, hidden_layer_size+1);

%%%%%% START PART 1
% for each example
for i = 1:m

    exampleVec = X(i, :);
    z2 = exampleVec * Theta1';          % 1 * n dimensions
    a2 = [ 1 sigmoid(z2) ];             % add bias node, 1 * (n + 1) then sigmoid function
    z3 = a2 * Theta2';                  % 1 * n dimensions
    a3 = sigmoid(z3)';                  % apply sigmoid function
    answerKey = (y(i) == labels);
    costFromExample = answerKey.*log(a3) + (1 - answerKey).*log(1 - a3);
    J_total = J_total + sum(costFromExample);
    %hypothesis = predictionVec(a3);
    delta3 = (a3 - answerKey);
    delta2 = (Theta2'*delta3) .* sigmoidGradient(z2);
    delta2 = delta2(2,end);
    accummulator2 = accummulator2 + delta3*a2;

end

Theta1WithoutBias = Theta1(:, 2:end); % size(Theta1, 2)
Theta2WithoutBias = Theta2(:, 2:end); % size(Theta2, 2)
regularisationCostTheta1 = sum(sum(Theta1WithoutBias .* Theta1WithoutBias));
regularisationCostTheta2 = sum(sum(Theta2WithoutBias .* Theta2WithoutBias));
regularisationCost = regularisationCostTheta1 + regularisationCostTheta2;

% divide by the number of examples
J = (-1/m) * J_total + (lambda/(2*m))*regularisationCost;
gradientJ = (1/m) * accummulator2;

%%%%%% END PART 1





% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
