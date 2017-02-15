class PostEffects
{
private:
  std::vector< PostEffectPass*> _passes;

public:
  void push(PostEffectPass* pass)
  {
    _passes.push_back(pass);
  }
  void pop()
  {
    _passes.pop_back();
  }
  void renderPostEffects(Framebuffer* target, VertexArray* quad)
  {
    target->bind();
    quad->bind();
    for(auto pass: _passes)
    {
      pass->renderPass(target);
    }
    quad->undind();
  }
}
